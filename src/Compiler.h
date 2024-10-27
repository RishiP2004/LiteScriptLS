#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <string>
#include "ASTNode.h"

using namespace std;

/**
 * Compiler class responsible for generating assembly code from an Abstract Syntax Tree (AST).
 * It takes a collection of ASTNode objects and translates them into a corresponding assembly language representation.
 */
class Compiler {
public:
    /**
     * Constructor a Compiler instance with a given AST
     *
     * @param nodes A vector of ASTNode objects representing the parsed source code commands.
     */
    explicit Compiler(const vector<ASTNode>& nodes);

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
    void compile(const string& filename) const;

private:
    const vector<ASTNode>& ast; // Reference to the vector of ASTNode objects representing the program's structure.
};

#endif // COMPILER_H
