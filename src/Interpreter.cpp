#include "Interpreter.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Constructor initializes the interpreter with a reference to AST nodes
Interpreter::Interpreter(const std::vector<std::unique_ptr<ASTNode>>& nodes) : ast(nodes) {}

/**
 * Executes the AST by processing each node sequentially.
 * Calls executeNode on each node in the AST to perform actions.
 */
void Interpreter::execute() {
    for (const auto& node : ast) {
        executeNode(*node);  // Execute each AST node
    }
}

/**
 * Executes a single AST node based on its type (e.g., assignment, print).
 *
 * @param node - AST node to be executed
 */
void Interpreter::executeNode(const ASTNode& node) {
    if (node.type == ASSIGN) {
        // For assignment nodes, evaluate the right-hand expression and store the result
        if (node.children.size() == 1) {
            variables[node.value] = evaluateExpression(*node.children[0]);
        }
    } else if (node.type == PRINT) {
        performPrint(node);  // Handle print operation
    }
}

/**
 * Evaluates an expression node and returns its integer result.
 * Supports identifiers, numeric literals, and binary operations.
 *
 * @param node - AST node representing an expression
 * @return - integer result of the expression
 */
int Interpreter::evaluateExpression(const ASTNode& node) {
    if (node.type == IDENTIFIER) {
        // Check if the identifier has been defined
        if (variables.find(node.value) == variables.end()) {
            throw std::runtime_error("Undefined variable: " + node.value);
        }
        return variables[node.value];  // Return the stored value of the identifier
    }

    if (node.type == NUMBER) {
        // Convert the numeric string to an integer
        return std::stoi(node.value);
    }

    if (node.type == BINARY_OP) {
        // For binary operations, evaluate both the left and right expressions
        const auto* binOpNode = dynamic_cast<const BinaryOpNode*>(&node);
        const int leftValue = evaluateExpression(*binOpNode->children[0]);
        const int rightValue = evaluateExpression(*binOpNode->children[1]);

        // Perform the operation based on the operator type
        if (binOpNode->op == '+') {
            return leftValue + rightValue;
        }
        if (binOpNode->op == '-') {
            return leftValue - rightValue;
        }
    }
    // If the expression node type is unrecognized, throw an error
    throw std::runtime_error("Invalid expression node type.");
}

/**
 * Performs the print operation for PRINT nodes by outputting the variable value.
 *
 * @param node - AST node representing a print operation
 */
void Interpreter::performPrint(const ASTNode& node) {
    if (variables.find(node.value) != variables.end()) {
        // Output the stored value of the variable
        std::cout << "Result: " << variables[node.value] << std::endl;
    } else {
        // Throw an error if the variable is not defined
        throw std::runtime_error("Undefined variable: " + node.value);
    }
}
