
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "Scanner.h"
#include "common.h"
#include "vm.h" // Include the header file where initVM is declared
// #include "chunk.h"
#include "debug.h" // For disassembleChunk

bool haderror = false;

static void repl() {
    char line[1024];
    for (;;) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
        printf("\n");
        break;
        }
        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc(fileSize + 1);

    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}

static void runFile(const char* path) {
    char* source = readFile(path);
    cout << "Starting" <<endl;
    InterpretResult result = interpret(source);
    free(source); // [owner]

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, char** argv) {
    // if (argc != 2) {
    //     std::cerr << "Usage: scanner <source file>" << std::endl;
    //     return 1;
    // }

    // std::ifstream file(argv[1]);
    // if (!file) {
    //     std::cerr << "Could not open file: " << argv[1] << std::endl;
    //     return 1;
    // }

    // std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // Scanner scanner(source);
    // std::vector<Token> tokens = scanner.scanTokens();

    // for (const Token& token : tokens) {
    //     std::cout << "Token(" << static_cast<int>(token.type) << ", \"" << token.lexeme << "\", Line " << token.line << ")" << std::endl;
    // }
    initVM(); 


    if(argc==1){
        repl();
    }
    else if(argc == 2){
        runFile(argv[1]);
    }
    else{
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    // Chunk chunk;
    // initChunk(&chunk);
    // int constant = addConstant(&chunk, 1.2);
    // writeChunk(&chunk, (OP_CONSTANT),123);
    // writeChunk(&chunk, constant,123);


    // constant = addConstant(&chunk, 3.4);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);
    // writeChunk(&chunk, OP_ADD, 123);
    // constant = addConstant(&chunk, 5.6);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);
    // writeChunk(&chunk, OP_DIVIDE, 123);

    // writeChunk(&chunk, (OP_NEGATE), 123);
    // writeChunk(&chunk, (OP_RETURN),123);
    // // disassembleChunk(&chunk, "test chunk");
    // interpret(&chunk);
    freeVM();
    // freeChunk(&chunk);

    return 0;
}

