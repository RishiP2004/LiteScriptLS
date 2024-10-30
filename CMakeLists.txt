cmake_minimum_required(VERSION 3.10)
project(LiteScript)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cpp
        src/LiteScript.cpp
        src/LiteScript.h
        src/Compiler.cpp
        src/Compiler.h
        src/Interpreter.cpp
        src/Interpreter.h
        src/Lexer.cpp
        src/Lexer.h
        src/Parser.cpp
        src/Parser.h
        src/AST.h
)

add_executable(LiteScript ${SOURCES})

# Specify the full path to objcopy if needed
set(OBJCOPY "C:/Program Files/JetBrains/CLion 2024.2.2/bin/mingw/bin/objcopy.exe")  # Adjust path as necessary

add_custom_command(TARGET LiteScript POST_BUILD
        COMMAND ${OBJCOPY} -O binary $<TARGET_FILE:LiteScript> ${CMAKE_CURRENT_BINARY_DIR}/output.asm
        COMMENT "Converting LiteScript to output.asm"
)