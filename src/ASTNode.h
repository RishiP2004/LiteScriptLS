#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>
#include <utility>

using namespace std;
/**
 * Enum representing the different types of nodes in the Abstract Syntax Tree (AST).
 * Each type corresponds to a specific operation or action that LiteScript supports.
 */
enum NodeType {
    ASSIGN,   // Node type for variable assignment
    ADD,      // Node type for addition operation
    SUBTRACT, // Node type for subtraction operation
    PRINT     // Node type for print operation
};
/**
 * Struct representing a node in the Abstract Syntax Tree (AST).
 * Each ASTNode can represent different operations depending on its type.
 */
struct ASTNode {
    NodeType type;                  // Type of the node (see enum)
    string var;                     // Name of the variable (used in ASSIGN and PRINT nodes)
    int value;                      // Constant value used in ASSIGN nodes
    vector<string> operands;        // List of operand variable names (used in ADD and SUBTRACT nodes)

    /**
     * Constructor for the ASTNode struct.
     * Initializes an ASTNode with the given type, variable name, value, and operands.
     *
     * @param t Type of the AST node (NodeType).
     * @param v Variable name associated with the node (default empty string).
     * @param val Constant value associated with the node (default 0).
     * @param ops List of operands for arithmetic operations (default empty vector).
     */
    explicit ASTNode(const NodeType t, string v = "", const int val = 0, vector<string> ops = {})
        : type(t), var(move(v)), value(val), operands(move(ops)) {}
};

#endif // ASTNODE_H
