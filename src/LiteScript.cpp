#include "Litescript.h"
#include <fstream>
#include <stdexcept>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "Interpreter.h"

/**
 * Loads a source file, tokenizes its contents, and parses it into an AST.
 *
 * @param filename - the name of the source file to load
 */
void LiteScript::loadFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    // Read the entire file contents into a string
    const std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Lexical analysis: tokenize the source code
    Lexer lexer(source);
    const std::vector<Token> tokens = lexer.tokenize();

    // Parse the tokens into an Abstract Syntax Tree (AST)
    Parser parser(tokens);
    parser.parse(&ast);
}

/**
 * Interprets the loaded AST by executing each node in sequence.
 */
void LiteScript::interpret() const {
    Interpreter interpreter(ast);
    interpreter.execute();
}

/**
 * Compiles the loaded AST into an assembly file.
 *
 * @param filename - the name of the output assembly file
 */
void LiteScript::compile(const std::string& filename) const {
    Compiler compiler(ast);
    compiler.compile(filename);
}
