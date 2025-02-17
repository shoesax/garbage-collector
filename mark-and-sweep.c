#include <stdlib.h>

#include "mark-and-sweep.h"

static void mark(Object *object) {
    if (object->marked) return;
    object->marked = 1; 
    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

static void markAll(VM *vm) {
    for(int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

static void sweep(VM *vm) {
    Object **object = &(vm->firstObject);
    while (*object != NULL) {
        if (!(*object)->marked) {
            Object *unreached = *object;
            *object = unreached->next;
            free(unreached);
            vm->numObjects -= 1;
        }
        else {
            (*object)->marked = 0;
            object = &((*object)->next);
        }

    }
}

void garbageCollector(VM* vm) {
    int numObjects = vm->numObjects;
    markAll(vm);
    sweep(vm);

    vm->maxObjects = vm->numObjects * 2;  
}