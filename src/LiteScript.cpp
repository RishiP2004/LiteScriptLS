#include "LiteScript.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Compiler.h"
#include "Interpreter.h"

using namespace std;

/**
 * Loads and parses a LiteScript file, converting its contents into an Abstract Syntax Tree (AST).
 *
 * This method reads each line of the specified script file, parsing commands into AST nodes
 * for execution or compilation.
 *
 * @param filename  The path to the script file to be loaded and parsed.
 * @throws runtime_error If the file cannot be opened.
 */
void LiteScript::loadFile(const string& filename) {
    // Open the filestream
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }
    string line;

    // Process each line to generate appropriate AST nodes
    while (getline(file, line)) {
        istringstream iss(line);
        string command;

        if (line.find("let") == 0) { // Parse 'let' command for variable assignment
            string var, equalSign;
            iss >> command >> var >> equalSign; // Extract 'let', variable name, and '='

            vector<string> operands;
            string operand;
            string operationType;

            // Parse the remainder of the line for operands and operators
            while (iss >> operand) {
                if (operand == "+" || operand == "-") {
                    operationType = operand;  // Identify operation type (addition or subtraction)
                } else {
                    operands.push_back(operand); // Collect operand values
                }
            }
            // Generate the appropriate AST node based on the parsed operation type
            if (operationType == "+") {
                ast.push_back(ASTNode(ADD, var, 0, operands)); // Create an ADD operation node
            } else if (operationType == "-") {
                ast.push_back(ASTNode(SUBTRACT, var, 0, operands)); // Create a SUBTRACT operation node
            } else if (operands.size() == 1) { // Handle simple variable assignment with one operand
                ast.push_back(ASTNode(ASSIGN, var, stoi(operands[0]))); // Create an ASSIGN node
            } else {
                // Handle cases with mixed operations like "let c = a + b"
                if (!operationType.empty()) {
                    if (operationType == "+") {
                        ast.push_back(ASTNode(ADD, var, 0, operands)); // Create an ADD operation node
                    } else if (operationType == "-") {
                        ast.push_back(ASTNode(SUBTRACT, var, 0, operands)); // Create a SUBTRACT operation node
                    }
                }
            }
        } else if (line.find("show") == 0) { // Parse 'show' command for outputting variable values
            string var;
            iss >> command >> var;  // Extract 'show' command and variable name
            ast.push_back(ASTNode(PRINT, var)); // Create a PRINT node for the specified variable
        }
    }
    // Close the filestream
    file.close();
}
/**
 * Executes the LiteScript commands in the AST by interpreting each node.
 *
 * This method initializes an Interpreter instance with the AST and executes each command
 * sequentially, supporting runtime behavior for assignments, operations, and printing output.
 */
void LiteScript::interpret() const {
    Interpreter interpreter(ast); // Initialize the Interpreter with the AST structure
    interpreter.execute(); // Process and execute each command in the AST
}

/**
 * Compiles the AST into a target assembly file, translating LiteScript commands to assembly code.
 *
 * This method initializes a Compiler instance with the AST and generates an assembly file
 * with the specified filename. The compilation process allows LiteScript to be transformed
 * into a lower-level representation for performance optimization or platform-specific usage.
 *
 * @param filename The name of the output file to which the compiled code is written.
 */
void LiteScript::compile(const string& filename) const {
    const Compiler compiler(ast); // Initialize Compiler with the AST
    compiler.compile(filename); // Compile AST nodes to target assembly code in the specified file
}
