// Implement a stack using linked list
// Push: O(1), Pop: O(1)
// Advantage using linked list is that it is dynamic structure.
// We can allocate/free memory as and when needed.

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef enum
{
      SUCCESS=0,
      FAILURE
}errorCode;

typedef enum
{
      PUSH=0,
      POP,
      PRINT,
      EXIT
}stackOperation;

typedef struct node {
    int val;
    struct node *next;
}node;

uint8_t push(node **stack, int value)
{
    node *newNode;

    newNode = (node *)(malloc(sizeof(node)));

    if(NULL == newNode)
    {
        printf("Error in memory allocation\n");
        return FAILURE; 
    }

    newNode->val = value;
    newNode->next = *stack;
    *stack = newNode;
    return SUCCESS;
}

uint8_t pop(node **stack, int *value)
{
    node *orgStack=NULL;

    if(NULL == *stack)
    {
        printf("Stack is empty\n");
        return FAILURE;
    }

    *value = (*stack)->val;
    orgStack = *stack;
    *stack = (*stack)->next;
    free(orgStack);
  
    return SUCCESS;
}

uint8_t printStack(node *stack)
{ 
    if(NULL == stack)
    {
        printf("Stack is empty\n");
        return FAILURE; 
    } 

    while(stack != NULL)
    {
        printf("%d\n", stack->val);
        stack = stack->next;  
    }   
 
    return SUCCESS;
}

int main()
{
    int ops;
    int value;
    uint8_t status = SUCCESS;
    node *stack=NULL;

    while(1) {
	printf("Enter the operation- 0: Push Into Stack, 1: Pop from stack, 2: Print the stack, 3: Exit\n");
	scanf("%d", &ops);

	if(ops == PUSH) {
	    printf("Enter the value\n");
	    scanf("%d", &value);
	    status = push(&stack, value);
	    if(SUCCESS == status)
	    {
	       printf("Added value to stack successfully\n");
	    } else {
	       printf("Push Operation failed\n");
	    }
	}else if(ops == POP) {
	    status = pop(&stack, &value);
	    if(SUCCESS == status)
	    {
	       printf("Popped value: %d\n", value);
	    } else {
	       printf("Pop Operation failed\n");
	    }

	} else if(ops == PRINT) {
	   printf("Print the stack\n");
           printStack(stack);
	} else if(ops == EXIT) {
	   printf("Exit\n");
           break;
	} else {
           printf("Invalid Operation\n");
        }
   } 
}
