#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <unordered_map>
#include "AST.h"
#include <memory>

/**
 * Interpreter class is responsible for executing an Abstract Syntax Tree (AST).
 * It processes each node in the AST, handling assignments, print operations, and expressions.
 */
class Interpreter {
public:
    /**
     * Initializes the interpreter with a reference to a vector of AST nodes.
     *
     * @param nodes - the AST nodes representing the program structure to be executed
     */
    explicit Interpreter(const std::vector<std::unique_ptr<ASTNode>>& nodes);

    /**
     * Executes the AST by processing each node in sequence.
     */
    void execute();

private:
    std::unordered_map<std::string, int> variables;  // Stores variable values for assignment operations
    const std::vector<std::unique_ptr<ASTNode>>& ast;  // Reference to AST nodes to be interpreted

    /**
     * Executes a single AST node based on its type (e.g., assignment, print).
     *
     * @param node - AST node to be executed
     */
    void executeNode(const ASTNode& node);

    /**
     * Evaluates an expression node and returns its integer result.
     *
     * @param node - AST node representing an expression
     * @return - integer result of the expression
     */
    int evaluateExpression(const ASTNode& node);

    /**
     * Performs a print operation for PRINT nodes, outputting the value of a variable.
     *
     * @param node - AST node representing a print operation
     */
    void performPrint(const ASTNode& node);
};

#endif // INTERPRETER_H
