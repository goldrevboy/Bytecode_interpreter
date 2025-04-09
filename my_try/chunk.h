#pragma once

#ifndef clox_chunk_h
#define clox_chunk_h
#include "common.h"
#include "value.h"

#endif
// chunk is essentially series of bytecode
typedef enum {
    OP_CONSTANT, // instruction to produce constants
    OP_NIL,
    OP_NOT,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_PRINT,
    OP_POP,
    OP_DEFINE_GLOBAL,
    OP_GET_GLOBAL,
    OP_SET_GLOBAL,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_JUMP_IF_FALSE,
    OP_JUMP ,
    OP_LOOP,
    OP_CALL,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE, // negate the value on top of the stack
    OP_RETURN // return from the current function
} OpCode;
// essentially each instruction is rep by a one-byte opcode

// byte code will have other data than just opcodes
// for example, the constant value to return
typedef struct {
    int count;
    int capacity;
    std::vector<uint8_t> code;
    ValueArray constants;
    std::vector<int> lines;
} Chunk; // we will use dynamic array to store bytecode

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte , int line);
int addConstant(Chunk* chunk, Value value);
