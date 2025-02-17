#include <stdio.h>

#include "object.h" 
#include "mark-and-sweep.h"

#define PRINT_TEST_LOG(x)    printf("%s \n", x)

static void printObject(Object* obj) {
    if (obj == NULL) {
        PRINT_TEST_LOG("NULL ptr passed. Exiting");
        return;
    }
    switch( obj->type) {
        case OBJ_INT:
            printf("%d \n", obj->value);
        case OBJ_PAIR:
            printObject(obj->head);
            printObject(obj->tail);
    }
}

static void testOne() {
    PRINT_TEST_LOG("Test to make sure we're not sweeping memory that is being used");
    VM *vm = newVM();

    pushInt(vm, 1);
    pushInt(vm, 2);

    garbageCollector(vm);

    if (vm->numObjects == 2) {
        PRINT_TEST_LOG("Correctly did not sweep 2 objects from stack space");
    }
    else {
        PRINT_TEST_LOG("Test failed");
    }
}

static void testTwo() {
    PRINT_TEST_LOG("Test to make sure unused memory is being swept");
    VM *vm = newVM();

    pushInt(vm, 10);
    pushInt(vm, 30);

    pop(vm);
    pop(vm);

    garbageCollector(vm);

    if (vm->numObjects == 0) {
        PRINT_TEST_LOG("Correctly swept objects from stack");
    }
    else {
        PRINT_TEST_LOG("Test failed");
    }
} 

static void testThree() {
    PRINT_TEST_LOG("Testing to see nested objects can be swept");

    VM* vm = newVM();

    pushInt(vm,5);
    pushInt(vm, 10);
    pushPair(vm);
    pushInt(vm, 15);
    pushInt(vm, 20);
    pushPair(vm);
    pushPair(vm);

    garbageCollector(vm);

    if (vm->numObjects == 7) {
        PRINT_TEST_LOG("Correctly did not sweep nested objects");
    }
    else {
        PRINT_TEST_LOG("Test failed");
    }
}

int main(int argc, char *argv[])
{
    testOne();
    testTwo();
    testThree();
    return 1;
}