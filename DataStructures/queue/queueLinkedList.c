// Implement a queue using linked list. 
// (Insert: O(n) , Remove: O(1), Dynamic allocation of memory)

#include<stdio.h>
#include<stdlib.h>

#define QUEUE_SIZE   256

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
}queueOperation;

typedef struct node
{
   int data;
   struct node *next; 
}node;

node *createNode(int value)
{
    node *newNode;

    newNode = (node *)(malloc(sizeof(node)));
    if(NULL == newNode)
    {
        printf("Error in memory allocation\n");
        return NULL; 
    } 
    newNode->data = value;
    newNode->next = NULL;
 
    return newNode;
}

status pushQ(node **Q, int value)
{
    node *newNode;
    node *myQ;

    newNode = createNode(value);
    if(NULL == newNode)
    {
        printf("Unable to create new node\n");   
        return FAILURE;
    }

    if(NULL == *Q)
    {
        *Q = newNode;
        return SUCCESS;
    } 

    myQ = *Q;
    while(myQ->next != NULL)
    {
        myQ = myQ->next;
    }
 
    myQ->next = newNode;

    return SUCCESS;  
}

status popQ(node **Q, int *value)
{
    node *orgHead;

    if(NULL == *Q)
    {
        printf("Queue is empty\n");
        return FAILURE; 
    }

    *value = (*Q)->data;
    orgHead = *Q;
    *Q = (*Q)->next;
    free(orgHead);
 
    return SUCCESS;    
}

status printQ(node *Q)
{
    if(NULL == Q)
    {
        printf("Queue is empty\n");
        return FAILURE;
    } 

    while(Q != NULL)
    {
        printf("%d\n", Q->data);
        Q = Q->next;
    }

    return SUCCESS;
}


int main()
{
   int ops;
   int exitFromMainLoop = 0;
   int value; 
   node *Q=NULL;
   status ret = SUCCESS;

   while(1) 
   { 
       printf("Enter the operation for the queue\n");
       scanf("%d", &ops);

       switch(ops) {
           case PUSH:
               printf("Enter the value to be pushed\n");
               scanf("%d", &value);
               ret = pushQ(&Q, value);
               if(FAILURE == ret)
               {
                   printf("Error in pushing element into the queue\n");
               }  
               break; 
                
           case POP:
               ret = popQ(&Q, &value);
               if(FAILURE == ret) {
                   printf("Error in popping elemnet from the queue\n");
               } else {
                   printf("Popped value is %d\n", value); 
               }
               break; 
               
           case PRINT:
               ret = printQ(Q);
               if(FAILURE == ret)
               {
                   printf("Error in printing the queue\n");
               }  
               break; 

           case EXIT:
               exitFromMainLoop = 1;
               break;  

           default:
               printf("Invalid Operation\n");
               break;              
       }
       if(exitFromMainLoop){
           break;  
       }
       printf("\n");  
   }

}



