#include <stdlib.h>
#include <assert.h>

#include "object.h"

Object* pop(VM *vm) {
    assert(vm->stackSize > 0);
    return vm->stack[--vm->stackSize];
}

static void push(VM *vm, Object* value) {
    assert(vm->stackSize < STACK_MAX);
    vm->stack[vm->stackSize++] = value;
}

static Object* newObject(VM *vm, eObjectType type) {
    Object *object = (Object*) malloc(sizeof(Object));
    object->type = type;
    object->marked = 0;

    object->next = vm->firstObject;
    vm->firstObject = object;
    vm->numObjects += 1;
    return object;
}

VM *newVM() {
    VM *vm = (VM*) malloc(sizeof(VM));
    vm->numObjects = 0;
    vm->maxObjects = 
    vm->stackSize = 0;
    vm->firstObject = NULL;
    return vm;
}

void pushInt(VM *vm, int value) {
    Object *object = newObject(vm, OBJ_INT);
    object->value = value;
    push(vm, object);   
}

Object *pushPair(VM *vm) {
    Object *object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);
    
    push(vm, object);
    return object;
}