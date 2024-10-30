#include "Parser.h"
#include <iostream>
#include "AST.h"
#include <memory>

// Constructor initializes the parser with a token sequence
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

/**
 * Parses the tokens and constructs an Abstract Syntax Tree (AST).
 * Adds parsed nodes to the provided AST vector.
 *
 * @param ast - pointer to a vector where AST nodes will be stored
 */
void Parser::parse(std::vector<std::unique_ptr<ASTNode>> *ast) {
    while (!isAtEnd()) {
        // Parse 'let' statements
        if (tokens[current].type == TokenType::LET) {
            consume(TokenType::LET);  // Consume 'let' keyword
            ast->push_back(parseLetStatement());
        }
        // Parse 'show' statements
        else if (tokens[current].type == TokenType::SHOW) {
            consume(TokenType::SHOW);  // Consume 'show' keyword
            ast->push_back(parseShowStatement());
        } else {
            // Handle unexpected tokens with an error message
            std::cerr << "Error: Unexpected token " << tokens[current].lexeme << "\n";
            current++;
        }
    }
}

/**
 * Parses a 'let' statement, expecting an identifier, '=', and an expression.
 *
 * @return an AST node representing the assignment
 */
std::unique_ptr<ASTNode> Parser::parseLetStatement() {
    if (isAtEnd() || tokens[current].type != TokenType::IDENTIFIER) {
        std::cerr << "Error: Expected identifier after 'let'\n";
        return nullptr;
    }
    std::string var = tokens[current++].lexeme;  // Capture the variable name
    consume(TokenType::EQUALS);  // Expect and consume '='

    auto value = expression();  // Parse the expression for assignment

    // Confirm expression is valid
    if (!value) {
        std::cerr << "Error: Expression in 'let' statement is null.\n";
        return nullptr;
    }
    if (value->value.empty() && value->type != BINARY_OP) {
        std::cerr << "Error: Expression value is empty in 'let' statement for variable: " << var << "\n";
        return nullptr;
    }
    consume(TokenType::SEMICOLON);  // Expect and consume ';' to end the statement

    // Create and return an AST node for the assignment
    std::vector<std::unique_ptr<ASTNode>> children;
    children.push_back(std::move(value));
    return std::make_unique<ASTNode>(ASSIGN, var, std::move(children));
}

/**
 * Parses a 'show' statement, expecting an identifier to be printed.
 *
 * @return an AST node representing the print operation
 */
std::unique_ptr<ASTNode> Parser::parseShowStatement() {
    if (isAtEnd() || tokens[current].type != TokenType::IDENTIFIER) {
        std::cerr << "Error: Expected identifier after 'show'\n";
        return nullptr;
    }
    std::string var = tokens[current++].lexeme;  // Capture the variable name

    if (!isAtEnd() && tokens[current].type == TokenType::SEMICOLON) {
        consume(TokenType::SEMICOLON);  // Expect and consume ';'
    } else {
        std::cerr << "Error: Expected ';' at the end of 'show' statement\n";
        return nullptr;
    }
    return std::make_unique<ASTNode>(PRINT, var);
}

/**
 * Parses an expression, including binary operations with identifiers and numbers.
 *
 * @return an AST node representing the expression
 */
std::unique_ptr<ASTNode> Parser::expression() {
    std::unique_ptr<ASTNode> left;

    // Parse the left operand
    if (tokens[current].type == TokenType::IDENTIFIER) {
        std::string firstOperand = tokens[current++].lexeme;
        left = std::make_unique<ASTNode>(IDENTIFIER, firstOperand);
    } else if (tokens[current].type == TokenType::NUMBER) {  // Handle numeric literals
        std::string numberValue = tokens[current++].lexeme;
        left = std::make_unique<ASTNode>(NUMBER, numberValue);
    } else {
        std::cerr << "Error: Expected identifier or number, got " << tokens[current].lexeme << "\n";
        return nullptr;
    }

    // Parse binary operators and right operands
    while (!isAtEnd() && (tokens[current].type == TokenType::PLUS || tokens[current].type == TokenType::MINUS)) {
        char op = tokens[current++].lexeme[0];  // Capture the operator

        // Parse right operand (identifier or number)
        if (tokens[current].type == TokenType::IDENTIFIER || tokens[current].type == TokenType::NUMBER) {
            std::string rightOperand = tokens[current++].lexeme;
            auto right = std::make_unique<ASTNode>(tokens[current - 1].type == TokenType::IDENTIFIER ? IDENTIFIER : NUMBER, rightOperand);
            left = std::make_unique<BinaryOpNode>(std::move(left), std::move(right), op);  // Create BinaryOpNode
        } else {
            std::cerr << "Error: Expected identifier or number after operator " << op << "\n";
            return nullptr;
        }
    }
    return left;
}

/**
 * Consumes a token of the specified type, advancing the parser position.
 * Logs an error if the token does not match the expected type.
 *
 * @param type - the expected type of the next token
 */
void Parser::consume(TokenType type) {
    if (tokens[current].type == type) {
        current++;
    } else {
        std::cerr << "Error: Expected token type " << static_cast<int>(type)
                  << ", but got token " << tokens[current].lexeme
                  << " of type " << static_cast<int>(tokens[current].type) << "\n";
        if (tokens[current].type != TokenType::END) {
            current++;  // Skip only if not at the end to avoid moving past the last token
        }
    }
}

/**
 * Checks if the parser has reached the end of the token stream.
 *
 * @return true if at the end of the tokens, false otherwise
 */
bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::END;
}
