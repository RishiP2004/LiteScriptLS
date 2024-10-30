#include "Lexer.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

// Constructor initializes the Lexer with the source code to tokenize
Lexer::Lexer(std::string source) : source(std::move(source)) {}

/**
 * Tokenizes the source code into a vector of tokens.
 *
 * Reads through each character, identifies token types, and adds tokens to the list.
 * @return a vector of tokens
 */
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();  // Skip any whitespace between tokens
        if (isAtEnd()) break;

        const char c = peek();

        // Match keywords and literals
        if (c == 'l' && matchKeyword("let", TokenType::LET, tokens)) continue;
        if (c == 's' && matchKeyword("show", TokenType::SHOW, tokens)) continue;
        if (isdigit(c)) {
            // Tokenize a number
            const std::string number = consumeNumber();
            tokens.push_back({TokenType::NUMBER, number});
        } else if (isalpha(c)) {
            // Tokenize an identifier
            const std::string id = consumeIdentifier();
            tokens.push_back({TokenType::IDENTIFIER, id});
        } else {
            // Tokenize symbols and throw error for unknown characters
            if (c == '+') {
                tokens.push_back({TokenType::PLUS, "+"});
                advance();
            } else if (c == '-') {
                tokens.push_back({TokenType::MINUS, "-"});
                advance();
            } else if (c == '=') {
                tokens.push_back({TokenType::EQUALS, "="});
                advance();
            } else if (c == ';') {
                tokens.push_back({TokenType::SEMICOLON, ";"});
                advance();
            } else {
                throw std::runtime_error("Invalid character: " + std::string(1, c));
            }
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}

/**
 * Advances the current position and returns the character at the new position.
 *
 * @return the next character in the source code
 */
char Lexer::advance() {
    return source[current++];
}

/**
 * Returns the current character without advancing the position.
 *
 * @return the current character in the source code
 */
char Lexer::peek() const {
    return isAtEnd() ? '\0' : source[current];
}

/**
 * Consumes a sequence of digits as a number.
 * Reads characters while they are digits and returns them as a string.
 *
 * @return the numeric string
 */
std::string Lexer::consumeNumber() {
    std::string number;
    while (isdigit(peek())) number += advance();
    return number;
}

/**
 * Consumes a sequence of alphabetic characters as an identifier.
 * Reads characters while they are alphabetic and returns them as a string.
 *
 * @return the identifier string
 */
std::string Lexer::consumeIdentifier() {
    std::string id;
    while (isalpha(peek())) id += advance();
    return id;
}

/**
 * Skips whitespace characters in the source code by advancing the position.
 */
void Lexer::skipWhitespace() {
    while (!isAtEnd() && isspace(peek())) advance();
}

/**
 * Matches a specified keyword in the source code and adds it as a token if found.
 * Ensures the keyword is followed by a non-alphanumeric character to avoid partial matches.
 *
 * @param keyword - the keyword to match in the source code
 * @param type - the token type assigned if the keyword matches
 * @param tokens - the vector of tokens to add to if a match is found
 * @return true if the keyword matches, false otherwise
 */
bool Lexer::matchKeyword(const std::string& keyword, const TokenType type, std::vector<Token>& tokens) {
    if (source.substr(current, keyword.length()) == keyword && !isalnum(peekAt(current + keyword.length()))) {
        tokens.push_back({type, keyword});
        current += keyword.length();  // Advance past the matched keyword
        return true;
    }
    return false;
}

/**
 * Checks if the end of the source code has been reached.
 *
 * @return true if the current position is at the end, false otherwise
 */
bool Lexer::isAtEnd() const {
    return current >= source.length();
}

/**
 * Peeks at a character at a specific position without changing the current position.
 *
 * @param index - position to peek at
 * @return the character at the specified position, or '\0' if out of bounds
 */
char Lexer::peekAt(const size_t index) const {
    return index >= source.length() ? '\0' : source[index];
}
