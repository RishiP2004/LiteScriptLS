#include "Interpreter.h"
#include <iostream>

using namespace std;

/**
 * Interpreter class responsible for executing the commands represented by an Abstract Syntax Tree (AST).
 * It evaluates expressions and manages variable assignments based on the parsed source code.
 */
Interpreter::Interpreter(const vector<ASTNode>& nodes) : ast(nodes) {}

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
void Interpreter::execute() {
    std::unordered_map<std::string, int> variables; //Unordered map to store variable -> value mapping

    for (const auto& node : ast) {
        if (node.type == ASSIGN) {
            // Direct assignment to a variable
            variables[node.var] = node.value; // Assign the provided value
        } else if (node.type == ADD || node.type == SUBTRACT) {
            // Initialize result based on the first operand
            int result = 0;
            bool firstOperand = true;

            for (const auto& operand : node.operands) {
                // Check if operand is defined in variables map
                if (variables.find(operand) != variables.end()) {
                    int operandValue = variables[operand]; // Get the value of the variable

                    // Initialize result with the first operand's value
                    if (firstOperand) {
                        result = operandValue; // Use the first operand as the starting point
                        firstOperand = false; // Set flag to false for subsequent operands
                    } else {
                        // Depending on the operation type, add or subtract
                        if (node.type == ADD) {
                            result += operandValue; // Perform addition
                        } else if (node.type == SUBTRACT) {
                            result -= operandValue; // Perform subtraction
                        }
                    }
                } else {
                    throw std::runtime_error("Undefined variable: " + operand);
                }
            }
            // Store the result back into the variable associated with the node
            variables[node.var] = result;
        } else if (node.type == PRINT) {
            // Check if variable is defined before printing
            if (variables.find(node.var) != variables.end()) {
                cout << "Result: " << variables[node.var] << std::endl; // Print the value of the variable
            } else {
                throw std::runtime_error("Undefined variable: " + node.var);
            }
        }
    }
}
