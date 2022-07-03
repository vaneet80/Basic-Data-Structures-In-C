// Implement a queue using an array. 
// (Insert: O(1) , Remove: O(n))
// First in first out

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

typedef struct queue
{
    int front;
    int rear;
    int data[QUEUE_SIZE];  
}queue;

status initQ(queue **Q)
{
    *Q = (queue *)malloc(sizeof(queue));

    (*Q)->front = 0;
    (*Q)->rear = -1;
    
    return SUCCESS;
} 

status pushQ(queue *Q, int value)
{
    if(Q->rear == QUEUE_SIZE-1)
    {
        printf("Queue is full \n");
        return FAILURE;
    } 

    Q->rear++;
    Q->data[Q->rear] = value;
    return SUCCESS;  
}

status popQ(queue *Q, int *value)
{
    int i;

    if(Q->rear < Q->front)
    {
        printf("Queue is empty\n");
        return FAILURE;
    }

    *value = Q->data[Q->front];

    for(i=0; i < Q->rear; i++)
    {
        Q->data[i] = Q->data[i+1];
    }

    Q->rear--;

    return SUCCESS;
}

status printQ(queue *Q)
{
   int i;

   if(Q->rear < Q->front)
   {
       printf("Queue is empty\n");
       return FAILURE;
   }

   for(i=Q->front; i <= Q->rear; i++)
   {
       printf("%d\n", Q->data[i]);
   }

   return SUCCESS;
}

int main()
{
   int ops;
   int exitFromMainLoop = 0;
   int value; 
   queue *Q=NULL;
   status ret = SUCCESS;

   ret = initQ(&Q);
   if(FAILURE == ret)
   {
       printf("Error in queue intialization\n");
       return; 
   }
   printf("%d %d\n", Q->front, Q->rear); 

   while(1) 
   { 
       printf("Enter the operation for the queue\n");
       printf("PUSH: 0, POP: 1, PRINT: 2, EXIT: 3\n");
       scanf("%d", &ops);

       switch(ops) {
           case PUSH:
               printf("Enter the value to be pushed\n");
               scanf("%d", &value);
               ret = pushQ(Q, value);
               if(FAILURE == ret)
               {
                   printf("Error in pushing element into the queue\n");
               }  
               break; 
                
           case POP:
               ret = popQ(Q, &value);
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
   }

}



