#include "Compiler.h"
#include <fstream>
#include <stdexcept>

using namespace std;
/**
 * Compiler class is responsible for translating an Abstract Syntax Tree (AST) into assembly code.
 * It generates assembly instructions based on LiteScript language syntax and handles expressions,
 * variable assignments, and output operations.
 */
Compiler::Compiler(const vector<ASTNode>& nodes) : ast(nodes) {}

/**
 * Compiles the AST into assembly code for the LiteScript language.
 *
 * This function organizes the generated assembly code into three sections:
 * - Data Section: Stores initialized data such as format strings.
 * - BSS Section: Allocates memory for variables without initialization.
 * - Text Section: Contains the executable code for the program, including variable operations and system calls.
 *
 * @param filename The name of the output file where the assembly code will be saved.
 * @throws runtime_error If the output file cannot be opened for writing.
 */
void Compiler::compile(const string& filename) const {
    // Open the output file for writing the assembly code
    ofstream outFile(filename);

    // Check if the file was opened successfully
    if (!outFile.is_open()) {
        throw runtime_error("Could not open file for writing: " + filename);
    }
    // -------------------------
    // Data Section
    // -------------------------
    // Define the data section for initialized data
    outFile << "section .data\n"; // Changed .section to section
    // Define a format string for output
    outFile << "output_format db \"Result: %d\", 0\n"; // Adjusted format for NASM

    // -------------------------
    // BSS Section
    // -------------------------
    // Define the BSS section for uninitialized data (variable storage)
    outFile << "section .bss\n"; // Changed .section to section

    for (const auto& node : ast) {
        // Allocate space for variables that are assigned or used in arithmetic operations
        if (node.type == ASSIGN || node.type == ADD || node.type == SUBTRACT) {
            outFile << node.var << " resd 1\n"; // Reserve 4 bytes for each variable (1 DWORD)
        }
    }

   // -------------------------
    // Text Section
    // -------------------------
    // Define the text section for executable code
    outFile << "section .text\n"; // Changed .section to section
    outFile << "extern printf\n"; // Declare printf as an external symbol
    outFile << "global _start\n"; // Mark _start as a global symbol
    outFile << "_start:\n"; // Entry point of the program

    // Process each AST node and generate corresponding assembly instructions
    for (const auto& node : ast) {
        if (node.type == ASSIGN) {
            // Generate code for variable assignment
            outFile << "    mov dword [" << node.var << "], " << node.value << "\n"; // Move constant value into the variable
        }
        else if (node.type == ADD || node.type == SUBTRACT) {
            // Initialize the accumulator register (eax) with the first operand’s value
            outFile << "    mov eax, [" << node.operands[0] << "]\n"; // Adjusted to load from memory

            // Perform addition or subtraction for the remaining operands
            for (size_t i = 1; i < node.operands.size(); ++i) {
                if (node.type == ADD) {
                    outFile << "    add eax, [" << node.operands[i] << "]\n"; // Add the operand to the accumulator
                } else if (node.type == SUBTRACT) {
                    outFile << "    sub eax, [" << node.operands[i] << "]\n"; // Subtract the operand from the accumulator
                }
            }
            // Store the accumulated result in the variable
            outFile << "    mov dword [" << node.var << "], eax\n"; // Store result back to the variable
        }
        else if (node.type == PRINT) {
            // Prepare to print the value of a variable
            outFile << "    mov eax, [" << node.var << "]\n"; // Load the variable value into eax
            outFile << "    push eax\n"; // Push the value onto the stack for printf
            outFile << "    push output_format\n"; // Push the format string onto the stack
            outFile << "    call printf\n"; // Call the printf function
            outFile << "    add esp, 8\n"; // Clean up the stack after the call
        }
    }

    // -------------------------
    // Exit Program
    // -------------------------
    // Generate code to exit the program
    outFile << "    mov eax, 1\n"; // syscall number for exit
    outFile << "    xor ebx, ebx\n"; // exit code 0
    outFile << "    int 0x80\n"; // make the syscall

    // Close the output file
    outFile.close();
    // Run the assembly file
    system("nasm -f win32 output.asm -o ls.o");
    system("gcc ls.o -o LiteScript.exe");
    system("LiteScript.exe");
}
