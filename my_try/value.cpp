#include <stdlib.h>

#include "value.h"
#include "object.h"

void initValueArray(ValueArray& array) {
    array.count = 0;
    array.capacity = 0;
    array.values = {};
}


void freeValueArray(ValueArray& array) {
    array.values.clear();         // Removes all elements but keeps allocated capacity
    array.values.shrink_to_fit(); // Frees excess memory
    initValueArray(array);
}

void writeValueArray(ValueArray& array, Value value) {
    array.values.push_back(value);
    array.count++;
    array.capacity++;
}

void printValue(Value value) {
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL: printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        case VAL_OBJ:
            printObject(value);
            break;
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case VAL_BOOL: return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL: return true;
        case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        case VAL_OBJ: return AS_OBJ(a) == AS_OBJ(b);
        default:
            return false; // Unreachable.
    }
}