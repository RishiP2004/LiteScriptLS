#ifndef COMPILER_H
#define COMPILER_H

#include "AST.h"
#include <vector>
#include <string>
#include <memory>
#include <fstream>

/**
 * The Compiler class generates assembly code from an AST (Abstract Syntax Tree) and saves it to a file.
 * It provides methods to generate different sections of assembly code and handles the compilation
 * and execution of the generated code.
 */
class Compiler {
public:
    /**
     * Initializes the compiler with a reference to a vector of AST nodes.
     *
     * @param nodes - AST nodes representing the program structure to be compiled
     */
    explicit Compiler(const std::vector<std::unique_ptr<ASTNode>>& nodes);

    /**
     * Generates the complete assembly code from the AST and saves it to the specified file.
     *
     * @param filename - the name of the file where the assembly code will be written
     */
    void compile(const std::string& filename) const;

private:
    /**
     * Generates the .data section of the assembly file, including static data like output format.
     *
     * @param outFile - output file stream for writing the .data section
     */
    void generateDataSection(std::ofstream& outFile) const;

    /**
     * Generates the .bss section of the assembly file to reserve memory space for program variables.
     *
     * @param outFile - output file stream for writing the .bss section
     */
    void generateBssSection(std::ofstream& outFile) const;

    /**
     * Generates the .text section of the assembly file, containing the main program instructions.
     *
     * @param outFile - output file stream for writing the .text section
     */
    void generateTextSection(std::ofstream& outFile) const;

    /**
     * Generates assembly code for assignment operations.
     * Supports binary operations (e.g., addition, subtraction) and direct assignments.
     *
     * @param outFile - output file stream for assignment instructions
     * @param node - AST node representing an assignment operation
     */
    void generateAssignment(std::ofstream& outFile, const std::unique_ptr<ASTNode>& node) const;

    /**
     * Generates assembly code for print operations, displaying variable values using printf.
     *
     * @param outFile - output file stream for print instructions
     * @param node - AST node representing a print operation
     */
    void generatePrint(std::ofstream& outFile, const std::unique_ptr<ASTNode>& node) const;

    /**
     * Generates assembly code for program exit, using a system call to terminate execution.
     *
     * @param outFile - output file stream for exit instructions
     */
    void generateExit(std::ofstream& outFile) const;

    /**
     * Compiles and runs the generated assembly code using NASM and GCC.
     * Handles errors in assembly, linking, or execution.
     */
    void compileAndRun() const;

    const std::vector<std::unique_ptr<ASTNode>>& ast;  // Reference to the AST nodes to be compiled
};

#endif // COMPILER_H
