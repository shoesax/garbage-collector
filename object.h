#ifndef OBJECT_H
#define OBJECT_H

#define STACK_MAX               (256)
#define INITIAL_GC_THRESHOLD    (10)

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} eObjectType;

typedef struct sObject {
    struct sObject *next;
    unsigned char marked;
    eObjectType type;
    union {
        int value;
        struct {
            struct sObject *head;
            struct sObject *tail;
        };
    };
} Object;

typedef struct {
    int numObjects;
    int maxObjects;
    Object *firstObject;
    Object *stack[STACK_MAX];
    int stackSize;
} VM;

/**
 * @brief   Pop an object from the vm stack
 *
 * @param[in] vm    Pointer to VM
 *
 *
 * @return Pointer to popped object
 */
Object* pop(VM *vm);

/**
 * @brief   Create a new VM and allocate some space for it
 *
 *
 * @return  Pointer to new VM 
 */
VM *newVM();

/**
 * @brief Push a new integer onto vm's stack
 *
 * @param[in] vm        Pointer to vm
 * @param[in] value     Value to add   
 *
 * 
 * @return              None
 */
void pushInt(VM *vm, int value);

/**
 * @brief Push a pair of values onto the stack
 *
 * @param[in] vm Pointer to vm where pair should be pushed to
 *
 *
 * @return       Pointer to pushed object
 */
Object *pushPair(VM *vm);

#endif //OBJECT_H