// Implement a queue using doubly linked list.  (Even a singly linked list with head and tail will work)
// (Insert: O(1) , Remove: O(1), Dynamic allocation of memory)

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
   struct node *prev;
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
    newNode->prev = NULL;
 
    return newNode;
}

status pushQ(node **qHead, node **qTail, int value)
{
    node *newNode;

    newNode = createNode(value);
    if(NULL == newNode)
    {
        printf("Error in memory allocation\n");
        return FAILURE;  
    }

    if(*qTail == NULL)
    {
        *qTail = newNode;
        *qHead = newNode;
        return SUCCESS; 
    }

    (*qTail)->next = newNode;
    newNode->prev = *qTail;
    *qTail = newNode;
    

    return SUCCESS;

}

status popQ(node **qHead, node **qTail, int *value)
{
    node *orgHead;

    if(NULL == *qHead)
    {
        printf("Queue is empty\n");
        return FAILURE;    
    }

    *value = (*qHead)->data; 
    orgHead = *qHead;
    *qHead = (*qHead)->next;
    free(orgHead);
    if(*qHead == NULL)
    {
        *qTail = NULL;
    }else if(*qHead == *qTail)
    {
        (*qTail)->prev = NULL;
    } else {
       (*qHead)->prev = NULL;
    } 
   
    return SUCCESS;
}

status printQ(node *Q)
{
    if(NULL == Q)
    {
        printf("Queue is empty\n");
        return FAILURE;
    }

    while(NULL != Q)
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
   node *qHead=NULL, *qTail=NULL;
   status ret = SUCCESS;

   while(1) 
   { 
       printf("Enter the operation for the queue\n");
       scanf("%d", &ops);

       switch(ops) {
           case PUSH:
               printf("Enter the value to be pushed\n");
               scanf("%d", &value);
               ret = pushQ(&qHead, &qTail, value);
               if(FAILURE == ret)
               {
                   printf("Error in pushing element into the queue\n");
               }  
               break; 
                
           case POP:
               ret = popQ(&qHead, &qTail, &value);
               if(FAILURE == ret) {
                   printf("Error in popping elemnet from the queue\n");
               } else {
                   printf("Popped value is %d\n", value); 
               }
               break; 
               
           case PRINT:
               ret = printQ(qHead);
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
   }

}



