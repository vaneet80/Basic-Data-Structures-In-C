// Implement a Min-Heap
// Insert: log(n), Extract-Min: log(n)
// This data structure can be used at places where we need to extract the minimum/maximum repeatedly

#include<stdio.h>

#define HEAP_SIZE 256

typedef struct heap{
   int heap_last;
   int data[HEAP_SIZE+1]; 
}heap;

typedef enum{
   SUCCESS=0,
   FAILURE 
}status;

typedef enum{
   INSERT=0,
   EXTRACT_MIN,
   PRINT, 
   EXIT 
}heapOps;

void swap(int *a, int idx1, int idx2)
{
   int temp;
   temp = a[idx1];
   a[idx1] = a[idx2];
   a[idx2] = temp;
}

status insertInHeap(heap *myHeap, int value)
{
    int index;

    if(NULL == myHeap)
    {
        printf("Null pointer passed as heap\n");
        return FAILURE;
    }

    if(HEAP_SIZE == myHeap->heap_last+1){
        printf("Heap is full, can not insert\n");
        return SUCCESS;
    }

    myHeap->data[myHeap->heap_last] = value;
    index = myHeap->heap_last;
    myHeap->heap_last++;

    while(index >= 2 && myHeap->data[index] < myHeap->data[index/2]) {
         swap(myHeap->data, index, index/2);
         index = index/2;
    }
     
    return SUCCESS;    
}

status extractMinFromHeap(heap *myHeap, int *value)
{
    int index;

    if(NULL == myHeap){
        printf("Null pointer passed as heap\n");
        return FAILURE; 
    }

    if(1 == myHeap->heap_last){
       printf("Heap is empty\n");
       return FAILURE; 
    }
 
    *value = myHeap->data[1];
    myHeap->data[1] = myHeap->data[myHeap->heap_last-1];
    index = 1; 
    myHeap->heap_last--;

    while(2*index < myHeap->heap_last){
        if(2*index+1 < myHeap->heap_last) {
             if(myHeap->data[2*index+1] < myHeap->data[2*index]
                && myHeap->data[index] > myHeap->data[2*index+1]){
                 swap(myHeap->data, index, 2*index+1);
                 index = 2*index+1; 
             }else if(myHeap->data[index] > myHeap->data[2*index]){
                 swap(myHeap->data, index, 2*index);
                 index = 2*index;  
             }else{
                 break;
             } 
        }else{
             if(myHeap->data[index] > myHeap->data[2*index]){
                swap(myHeap->data, index, 2*index);
                index = 2*index;  
             }
             break;
        }
    }
  
    return SUCCESS;
}

status printHeap(heap *myHeap)
{
    int i;
 
    if(NULL == myHeap)
    {
        printf("Heap is null\n");
        return FAILURE;
    }

    if(myHeap->heap_last == 1){
        printf("Heap is empty\n");
        return FAILURE;
    }  

    for(i=1; i < myHeap->heap_last; i++)
    {
        printf("%d ", myHeap->data[i]);
    }
    printf("\n");
}

int main()
{
    heap myHeap;
    status ret;
    int ops;
    int value;
    int exitFromLoop=0;

    myHeap.heap_last=1;

    while(1){
        printf("Enter the operation\n");
        printf("INSERT:0, EXTRACT-MIN:1, PRINT:2, EXIT:3\n");
        scanf("%d", &ops);

        switch(ops){
            case INSERT:
                printf("Enter the value to be inserted in the heap\n");
                scanf("%d", &value);
                ret = insertInHeap(&myHeap, value);
                if(FAILURE == ret){
                    printf("Insert failed in heap\n");
                }
                break;

            case EXTRACT_MIN:
                ret = extractMinFromHeap(&myHeap, &value);
                if(FAILURE == ret){
                    printf("Extract Min failed\n");
                }else{
                    printf("Minimum value extracted is %d\n", value); 
                } 
                break;

            case PRINT:
                ret = printHeap(&myHeap);
                if(FAILURE == ret){
                    printf("Could not print the heap\n");
                } 
                break;

            case EXIT:
                exitFromLoop = 1;
                break;

            default:
                break;  
        }  
        if(exitFromLoop){
            break;
        }
    }
}




