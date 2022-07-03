#include<stdio.h>
#include<stdlib.h>


// Implement a circular queue using an array
// Insert: O(1), Remove: O(1)
// Disadvantage is that size is fixed.

#define QUEUE_SIZE  4

typedef struct queue
{
    int front;
    int rear;
    int data[QUEUE_SIZE]; 
}queue;

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
}queueOperations; 

status initQueue(queue **Q)
{
    *Q = (queue *) (malloc(sizeof(queue)));
    if(NULL == *Q)
    {      
       printf("Error in memory allocation\n");
       return FAILURE; 
    }

    (*Q)->front = 0;
    (*Q)->rear = 0;

    return SUCCESS;
}

status pushQueue(queue *Q, int value)
{
    if( (Q->rear > Q->front && Q->rear-Q->front == QUEUE_SIZE-1) 
      ||(Q->rear < Q->front && Q->front == (Q->rear+1)%QUEUE_SIZE) )
    {
        printf("Queue is full\n");
        return FAILURE; 
    }

    Q->rear = (Q->rear+1)%QUEUE_SIZE;
    Q->data[Q->rear] = value;

    return SUCCESS; 
}

status popQueue(queue *Q, int *value)
{
    if(Q->front == Q->rear)
    {
        printf("Queue is empty\n");
        return FAILURE;
    }

    Q->front = (Q->front+1) % QUEUE_SIZE;
    *value = Q->data[Q->front];

    return SUCCESS;
}

status printQueue(queue *Q)
{
    int i, start, end;

    if(Q->front == Q->rear)
    {
        printf("Queue is empty\n");
        return FAILURE;  
    }

    if(Q->front + 1 <= Q->rear)
    {
        start = Q->front+1;
        end = Q->rear;
    } else {
        start = Q->front+1;
        end = Q->rear + QUEUE_SIZE;
    } 
   
    for(i = start; i <= end; i++)
    {
        printf("%d\n", Q->data[i%QUEUE_SIZE]);   

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

   ret = initQueue(&Q);
   if(FAILURE == ret)
   {
       printf("Error in queue intialization\n");
       return; 
   }
  
   while(1) 
   { 
       printf("Enter the operation for the queue\n");
       printf("PUSH: 0, POP: 1, PRINT: 2, EXIT: 3\n");
       scanf("%d", &ops);

       switch(ops) {
           case PUSH:
               printf("Enter the value to be pushed\n");
               scanf("%d", &value);
               ret = pushQueue(Q, value);
               if(FAILURE == ret)
               {
                   printf("Error in pushing element into the queue\n");
               }  
               break; 
                
           case POP:
               ret = popQueue(Q, &value);
               if(FAILURE == ret) {
                   printf("Error in popping elemnet from the queue\n");
               } else {
                   printf("Popped value is %d\n", value); 
               }
               break; 
               
           case PRINT:
               ret = printQueue(Q);
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
       printf("\n"); 
       if(exitFromMainLoop){
           break;  
       }  
   }
}





