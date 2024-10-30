#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

/**
 * Enum class representing types of tokens that can be recognized by the Lexer.
 */
enum class TokenType {
    LET, SHOW, IDENTIFIER, NUMBER, PLUS, MINUS, EQUALS, SEMICOLON, END
};

/**
 * Struct representing a token with its type and lexeme (string representation).
 */
struct Token {
    TokenType type;
    std::string lexeme;
};

/**
 * Lexer class responsible for converting a source string into a sequence of tokens.
 * It provides methods to handle keywords, numbers, identifiers, and various symbols.
 */
class Lexer {
public:
    /**
     * Initializes the lexer with the source string to tokenize.
     * @param source - the source code as a string
     */
    explicit Lexer(std::string source);

    /**
     * Tokenizes the source string, returning a vector of recognized tokens.
     * @return - a vector of tokens representing the source code
     */
    std::vector<Token> tokenize();

private:
    std::string source;  // Source code to tokenize
    size_t current = 0;  // Current position in the source code

    /**
     * Advances the lexer by one character and returns it.
     *
     * @return - the current character before advancing
     */
    char advance();

    /**
     * Checks if the lexer has reached the end of the source string.
     *
     * @return - true if at the end of the source; false otherwise
     */
    [[nodiscard]] bool isAtEnd() const;

    /**
     * Returns the current character without advancing.
     *
     * @return - the current character
     */
    [[nodiscard]] char peek() const;

    /**
     * Peeks at a specific index without changing the current position.
     *
     * @param index - the index to peek at
     * @return - character at the specified index, or '\0' if out of bounds
     */
    [[nodiscard]] char peekAt(size_t index) const;

    /**
     * Skips any whitespace characters at the current position.
     */
    void skipWhitespace();

    /**
     * Consumes a sequence of numeric characters and returns them as a string.
     *
     * @return - the consumed number as a string
     */
    std::string consumeNumber();

    /**
     * Consumes a sequence of alphabetic characters, forming an identifier.
     *
     * @return - the consumed identifier as a string
     */
    std::string consumeIdentifier();

    /**
     * Matches a specific keyword if present at the current position.
     * Adds the token to the provided token vector if matched.
     *
     * @param keyword - the keyword to match
     * @param type - token type to use if matched
     * @param tokens - vector to add the matched token
     * @return - true if the keyword was matched; false otherwise
     */
    bool matchKeyword(const std::string& keyword, TokenType type, std::vector<Token>& tokens);
};

#endif // LEXER_H
