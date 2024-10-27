# LiteScript

## Overview
LiteScript is a custom programming language designed for fun and learning purposes, serving as a great introduction to the basics of how languages are compiled and interpreted.
It allows users to compile or interpret LiteScript coded scripts that have the extension .ls using `litescript <compile|interpret> <file.ls>`

## Features
- **Custom Syntax**: LiteScript syntax is simple, although limited - shows a great foundation
- **Compilation and Interpretation**: Users can choose to compile scripts for execution or interpret them directly.

## Tech Stack
- **C++**: The core language implementation is built using C++, providing performance and flexibility.
- **Netwide Assembler (NASM)**: LiteScript compiles into NASM assembly, which showcases the compilation for efficient low-level execution on platforms.
- **Custom Lexer and Parser**: LiteScript includes a lexer and parser to interpret the syntax and execute commands.

## Usage
1. **Installation**: Ensure you have a C++ compiler and NASM installed on your machine.
2. **Compile/Interpret**: Use the command `litescript <compile|interpret> <file.ls>` to run your scripts.
   - Replace `<file.ls>` with the path to your script file.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/RishiP2004/LiteScriptLS.git
   cd LiteScriptLS
   ```
2. **Compile the project**: Use your preferred C++ IDE to build the project or use a command line to compile the source code
3. Run the Application: After compiling, you can run your LiteScript files using the provided command.
