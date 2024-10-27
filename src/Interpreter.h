#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <unordered_map>
#include "ASTNode.h"

using namespace std;

/**
 * Interpreter class that evaluates and executes the commands represented by an Abstract Syntax Tree (AST).
 * It manages variable assignments and operations such as addition, subtraction, and printing of values.
 */
class Interpreter {
public:
    /**
     * Constructs an Interpreter instance with a given AST.
     *
     * @param nodes A vector of ASTNode objects representing the parsed source code commands.
     */
    explicit Interpreter(const vector<ASTNode>& nodes);

    /**
     * Executes the commands represented by the AST.
     * This function processes each AST node, performing assignments, calculations, and print operations.
     *
     * It maintains a mapping of variable names to their corresponding integer values.
     * The operations supported include:
     * - Assignment of constant values to variables
     * - Addition and subtraction of variables
     * - Printing the value of variables
     *
     * @throws runtime_error if an attempt is made to access an undefined variable during execution.
     */
    void execute();

private:
    unordered_map<string, int> variables;  // Map that stores variable names and their corresponding integer values.
    const vector<ASTNode>& ast;            // Reference to the vector of ASTNode objects representing the program's structure.
};

#endif // INTERPRETER_H
