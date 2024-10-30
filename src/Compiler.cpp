#include "Compiler.h"
#include "AST.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <cctype>

// Constructor initializes the compiler with a vector of AST nodes
Compiler::Compiler(const std::vector<std::unique_ptr<ASTNode>>& nodes) : ast(nodes) {}

/**
 * Compiles the AST into assembly code and saves it to a file.
 *
 * Generates .data, .bss, and .text sections and then runs the generated code.
 * @param filename - name of the file to write assembly code
 */
void Compiler::compile(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    generateDataSection(outFile);   // Generate .data section for static data
    generateBssSection(outFile);    // Generate .bss section for variable storage
    generateTextSection(outFile);   // Generate .text section for main instructions
    compileAndRun();                   // Assemble, link, and execute the program
}

/**
 * Generates the .data section, including static data like the output format for printf.
 *
 * @param outFile - output file stream to write the .data section
 */
void Compiler::generateDataSection(std::ofstream& outFile) const {
    outFile << "section .data\n";
    outFile << "output_format db \"Result: %d\", 0\n";  // Defines format string for printing results
}

/**
 * Generates the .bss section, reserving memory for variables used in the program.
 *
 * @param outFile - output file stream to write the .bss section
 */
void Compiler::generateBssSection(std::ofstream& outFile) const {
    outFile << "section .bss\n";

    // Reserve space for each variable involved in assignment
    for (const auto& node : ast) {
        if (node->type == ASSIGN) {
            outFile << node->value << " resd 1\n";  // Reserve 4 bytes per variable
        }
    }
}

/**
 * Generates the .text section with main program instructions.
 *
 * @param outFile - output file stream for the .text section
 */
void Compiler::generateTextSection(std::ofstream& outFile) const {
    outFile << "section .text\n";
    outFile << "extern printf\n";
    outFile << "global _start\n";
    outFile << "_start:\n";

    // Generate code for each node in the AST
    for (const auto& node : ast) {
        if (node->type == ASSIGN) {
            generateAssignment(outFile, node);
        } else if (node->type == PRINT) {
            generatePrint(outFile, node);
        }
    }
    generateExit(outFile);  // Append code for program exit
}

/**
 * Generates assembly code for assignment operations.
 * Supports binary operations and direct assignments of literals/identifiers.
 *
 * @param outFile - output file stream for assembly code
 * @param node - AST node representing an assignment
 */
void Compiler::generateAssignment(std::ofstream& outFile, const std::unique_ptr<ASTNode>& node) const {
    if (node->children[0]->type == BINARY_OP) {
        const auto* binOpNode = dynamic_cast<const BinaryOpNode*>(node->children[0].get());

        if (!binOpNode || binOpNode->children.size() < 2) {
            std::cerr << "Error: Invalid BinaryOpNode in assignment.\n";
            return;
        }
        // Generate binary operation code
        outFile << "    mov eax, dword [" << binOpNode->children[0]->value << "]\n";

        for (size_t i = 1; i < binOpNode->children.size(); ++i) {
            const auto& rightOperand = binOpNode->children[i]->value;

            if (binOpNode->op == '+') {
                outFile << "    add eax, dword [" << rightOperand << "]\n";
            } else if (binOpNode->op == '-') {
                outFile << "    sub eax, dword [" << rightOperand << "]\n";
            }
        }
        outFile << "    mov dword [" << node->value << "], eax\n";  // Store result
    } else {
        // Handle assignment of literals or identifiers
        const std::string& childValue = node->children[0]->value;

        if (std::isdigit(childValue[0])) {
            outFile << "    mov eax, " << childValue << "\n";
        } else {
            outFile << "    mov eax, dword [" << childValue << "]\n";
        }
        outFile << "    mov dword [" << node->value << "], eax\n";
    }
}

/**
 * Generates assembly code for print operations in the AST, using printf.
 *
 * @param outFile - output file stream for assembly code
 * @param node - AST node representing a print operation
 */
void Compiler::generatePrint(std::ofstream& outFile, const std::unique_ptr<ASTNode>& node) const {
    if (node->value.empty()) {
        std::cerr << "Error: Empty value in print statement.\n";
        return;
    }
    outFile << "    mov eax, dword [" << node->value << "]\n";
    outFile << "    push eax\n";
    outFile << "    push output_format\n";
    outFile << "    call printf\n";
    outFile << "    add esp, 8\n";  // Clean up the stack after printf
}

/**
 * Generates assembly code for program exit, terminating execution with exit code 0.
 *
 * @param outFile - output file stream for assembly code
 */
void Compiler::generateExit(std::ofstream& outFile) const {
    outFile << "    mov eax, 1\n";   // System call for exit
    outFile << "    xor ebx, ebx\n"; // Exit code 0
    outFile << "    int 0x80\n";     // Interrupt to terminate the program
}

/**
 * Compiles the generated assembly code with NASM and GCC, then runs the executable.
 * Handles errors during assembly, linking, or execution.
 */
void Compiler::compileAndRun() const {
    if (system("nasm -f win32 output.asm -o ls.o") != 0) {
        std::cerr << "Error: NASM compilation failed.\n";
        return;
    }
    if (system("gcc ls.o -o LiteScript.exe") != 0) {
        std::cerr << "Error: Linking failed.\n";
        return;
    }
    if (system("LiteScript.exe") != 0) {
        std::cerr << "Error: Execution failed.\n";
    }
}
