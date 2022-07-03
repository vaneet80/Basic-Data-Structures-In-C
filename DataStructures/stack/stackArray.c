#include<stdio.h>
#include<stdint.h>

// Implement a stack using an array
// Push: O(1), Pop: O(1)
// Last in first out for stack

#define STACK_SIZE  100

typedef struct stack{
  int stackPointer;
  int data[STACK_SIZE];
}stack;

typedef enum
{
      SUCCESS=0,
      FAILURE
}status;

typedef enum
{
      PUSH=0,
      POP,
      PRINT,
      EXIT
}stackOperation;

status initStack(stack *st)
{
    st->stackPointer = -1;
    return SUCCESS;
}

status  push(stack *st, int value)
{
     if(st->stackPointer+1 < STACK_SIZE)
     {       
            st->stackPointer++;
            st->data[st->stackPointer] = value; 
            return SUCCESS;
     } else {
            printf("Stack is full\n");
            return FAILURE;
     }
} 

status  pop(stack *st, int *value)
{
      if(st->stackPointer == -1)
      {
             printf("Stack is empty\n");
             return FAILURE;
      } else {
             *value = st->data[st->stackPointer];
             st->stackPointer--;
             return SUCCESS;  
      }
}

status printStack(stack st)
{
    int i;

    if(st.stackPointer == -1) {
       printf("Nothing to print, the stack is empty\n");
       return;
    }

    for(i=0; i <= st.stackPointer; i++)
    {
        printf("%d\n", st.data[i]);
    }

    return SUCCESS;
}



int main()
{
    int ops;
    int value;
    uint8_t status = SUCCESS;
    stack myStack;

    status = initStack(&myStack);
    if(SUCCESS == status)
    {
       printf("Stack intialization done successfully\n");
    }

    while(1) {
	printf("Enter the operation- 0: Push Into Stack, 1: Pop from stack, 2: Print the stack, 3: Exit\n");
	scanf("%d", &ops);

	if(ops == PUSH) {
	    printf("Enter the value\n");
	    scanf("%d", &value);
	    status = push(&myStack, value);
	    if(SUCCESS == status)
	    {
	       printf("Added value to stack successfully\n");
	    } else {
	       printf("Push Operation failed\n");
	    }
	}else if(ops == POP) {
	    status = pop(&myStack, &value);
	    if(SUCCESS == status)
	    {
	       printf("Popped value: %d\n", value);
	    } else {
	       printf("Pop Operation failed\n");
	    }

	} else if(ops == PRINT) {
	   printf("Print the stack\n");
           printStack(myStack);
	} else if(ops == EXIT) {
	   printf("Exit\n");
           break;
	} else {
           printf("Invalid Operation\n");
        }
   } 
}
