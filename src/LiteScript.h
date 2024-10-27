#ifndef LITESCRIPT_H
#define LITESCRIPT_H

#include <vector>
#include <string>
#include "ASTNode.h"

using namespace std;

// LiteScript class for managing the loading, interpreting, and compiling of scripts
class LiteScript {
public:
    /**
     * Loads and parses a LiteScript file, converting its contents into an Abstract Syntax Tree (AST).
     *
     * This method reads each line of the specified script file, parsing commands into AST nodes
     * for execution or compilation.
     *
     * @param filename  The path to the script file to be loaded and parsed.
     * @throws runtime_error If the file cannot be opened.
     */
    void loadFile(const string& filename);
    /**
     * Executes the LiteScript commands in the AST by interpreting each ASTNode.
     *
     * This method initializes an Interpreter instance with the AST and executes each command
     * sequentially, supporting runtime behavior for assignments, operations, and printing output.
     */
    void interpret() const;
    /**
     * Compiles the AST into a target assembly file, translating LiteScript commands to assembly code.
     *
     * This method initializes a Compiler instance with the AST and generates an assembly file
     * with the specified filename. The compilation process allows LiteScript to be transformed
     * into a lower-level representation for performance optimization or platform-specific usage.
     *
     * @param filename The name of the output file to which the compiled code is written.
     */
    void compile(const string& filename) const;

private:
    std::vector<ASTNode> ast; // Vector to store the AST generated from loadFile
};

#endif // LITESCRIPT_H
