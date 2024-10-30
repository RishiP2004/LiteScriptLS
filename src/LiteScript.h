#ifndef LITESCRIPT_H
#define LITESCRIPT_H

#include <vector>
#include <string>
#include <memory>
#include "AST.h"

/**
 * LiteScript class is responsible for managing the overall workflow:
 * loading a source file, parsing it into an AST, interpreting the AST,
 * and compiling it to an assembly file if needed.
 */
class LiteScript {
public:
    /**
     * Loads a source file, tokenizes and parses it, and generates an AST.
     * @param filename - the name of the source file to load
     */
    void loadFile(const std::string& filename);

    /**
     * Interprets the loaded AST by executing each node sequentially.
     */
    void interpret() const;

    /**
     * Compiles the loaded AST into an assembly file.
     * @param filename - the name of the output assembly file
     */
    void compile(const std::string& filename) const;

private:
    std::vector<std::unique_ptr<ASTNode>> ast;  // Abstract Syntax Tree generated from source file
};

#endif // LITESCRIPT_H
