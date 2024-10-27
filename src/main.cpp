#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "LiteScript.h"

using namespace std;

int main(const int argc, char* argv[]) {
    LiteScript script; // Create an instance of LiteScript to manage script execution.

    // Check for correct number of command-line arguments
    if (argc != 3) {
        cerr << "Usage: ./litescript <action> <filename.ls>\n";
        cerr << "Actions: interpret, compile\n";
        return EXIT_FAILURE;
    }
    // Retrieve the action from the first argument
    string action = argv[1];

    if (action == "interpret") {
        try {
            script.loadFile(argv[2]); // Load and process the specified script file
            script.interpret(); // Interpret and execute the loaded commands
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return EXIT_FAILURE;
        }
    } else if (action == "compile") {
        try {
            script.loadFile(argv[2]); // Load and process the specified script file
            script.compile("output.asm"); // Compile the loaded commands into an assembly file
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return EXIT_FAILURE;
        }
    } else {
        cerr << "Unknown action: " << action << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
