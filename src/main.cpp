#include <iostream>
#include <fstream>
#include <string>
#include "LiteScript.h"

/**
 * Main entry point for the LiteScript interpreter/compiler.
 * This program accepts a source file and an action (interpret or compile) via command-line arguments.
 * It either interprets the file (runs it) or compiles it into an assembly file.
 *
 * Usage: ./litescript <action> <filename.ls>
 *
 * Actions:
 *   - interpret: Executes the source file directly
 *   - compile: Compiles the source file into an assembly file (output.asm)
 */
int main(const int argc, char* argv[]) {
    LiteScript lite_script; // Create an instance of LiteScript to manage script execution.

    // Check for correct number of command-line arguments
    if (argc != 3) {
        std::cerr << "Usage: ./litescript <action> <filename.ls>\n";
        std::cerr << "Actions: interpret, compile\n";
        return EXIT_FAILURE;
    }
    // Retrieve the action from the first argument
    const std::string action = argv[1];

    if (action == "interpret") {
        // Interpret and execute the script
        try {
            lite_script.loadFile(argv[2]);  // Load and process the specified script file
            lite_script.interpret();        // Interpret and execute the loaded commands
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    } else if (action == "compile") {
        // Compile the script into an assembly file
        try {
            lite_script.loadFile(argv[2]);       // Load and process the specified script file
            lite_script.compile("output.asm");    // Compile to an assembly file named output.asm
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        // Handle unknown actions
        std::cerr << "Unknown action: " << action << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
