#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

// Defines the types of nodes that can exist within the Abstract Syntax Tree (AST)
enum NodeType {
    ASSIGN,        // Assignment operation
    PRINT,         // Print operation
    IDENTIFIER,    // Variable identifier
    NUMBER,        // Numeric literal
    BINARY_OP      // Binary operation (e.g., addition, subtraction)
};

// Base class representing a generic node in the AST
class ASTNode {
public:
    NodeType type;  // Type of the AST node
    std::string value;  // Value associated with the node (e.g., variable name, number)
    std::vector<std::unique_ptr<ASTNode>> children;  // Children nodes, if any

    /**
     * Constructor for ASTNode without children
     *
     * @param type - the type of the node
     * @param value - the value associated with the node
     */
    ASTNode(const NodeType type, std::string value) : type(type), value(std::move(value)) {}

    /**
     * Constructor for ASTNode with children
     *
     * @param type - the type of the node
     * @param value - the value associated with the node
     * @param children - a vector of child nodes
     */
    ASTNode(const NodeType type, std::string value, std::vector<std::unique_ptr<ASTNode>> children)
        : type(type), value(std::move(value)), children(std::move(children)) {}

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~ASTNode() = default;
};

// Derived class for binary operations in the AST (e.g., addition, subtraction)
class BinaryOpNode final : public ASTNode {
public:
    char op;  // Character representing the operator (e.g., '+', '-')

    /**
     * Constructs a BinaryOpNode with left and right child nodes
     *
     * @param left - left operand node
     * @param right - right operand node
     * @param op - character representing the binary operator
     */
    BinaryOpNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, const char op)
        : ASTNode(BINARY_OP, ""), op(op) {
        // Initialize children with left and right operand nodes
        children.push_back(std::move(left));
        children.push_back(std::move(right));
    }
};

#endif
