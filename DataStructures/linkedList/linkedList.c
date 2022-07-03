#include<stdio.h>
#include<stdlib.h>

// Implement a singly linked list 
// Insert: O(n), Delete: O(n), Search: O(n)
// Linked list is dynamic, we allocate/free the memory as and when required
// Hence it is better than array, we can say it is dynamic array

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef enum
{
    SUCCESS=0,
    FAILURE
}status;

typedef enum
{
   INSERT=0,
   DELETE,
   SEARCH,
   PRINT,
   EXIT 
}linkedListOps;

node *createNode(int data)
{
   node *newNode;

   newNode = (node *)(malloc(sizeof(node)));
   if(NULL == newNode)
   {
      printf("Memory allocation failed\n");
      return newNode;
   }

   newNode->data = data;
   newNode->next = NULL;
   return newNode;
} 

status insertInLinkedList(node **list, int data)
{
   node *newNode;
   node *prevNode;
   node *myList;
 
   newNode = createNode(data);
   if(NULL == newNode)
   {
       printf("Could not create a new node\n");
       return FAILURE;
   }

   // List is empty, insert as head
   // This is why we needed to pass a double pointer to this function
   myList = *list;
   if(NULL == myList)
   {
       *list = newNode;
       return SUCCESS; 
   }

   while(myList != NULL)
   {
       prevNode = myList;
       myList = myList->next;
   } 

   prevNode->next = newNode;
   
   return SUCCESS;
}

status deleteFromLinkedList(node **list, int data)
{
   node *myList;
   node *prevNode;

   if(NULL == *list)
   {
       printf("Linked list is empty\n");
       return FAILURE; 
   }

   // data is at the head of the list
   // In this case head needs to be changed to the next node
   myList = *list;
   if(data == myList->data)
   {
      *list = (*list)->next;
      free(myList);
      return SUCCESS; 
   }

   while(myList != NULL)
   {
      if(data == myList->data)
      {
          prevNode->next = myList->next;
          free(myList);
          return SUCCESS; 
      } 
      prevNode = myList;
      myList = myList->next;

   }
  
   return FAILURE;
}

status searchInLinkedList(node *list, int data)
{
    while(list != NULL)
    {
       if(data == list->data)
       {
           printf("Data found in the list\n");
           return SUCCESS;
       } 
       list = list->next;
    }

    return FAILURE;
}

status printLinkedList(node *list)
{
    if(NULL == list)
    {
        printf("List is empty\n");
        return FAILURE;
    }

    while(list != NULL)
    {
        printf("%d\n", list->data);
        list = list->next;
    }

    return SUCCESS;
}

int main()
{
    int ops;
    int data; 
    int ret=SUCCESS;
    int exitFromMainLoop = 0;
    node *list;

    while(1)
    {
        printf("Enter the operation\n");
        printf("INSERT:0, DELETE:1, SEARCH:2, PRINT:3, EXIT:4\n");
        scanf("%d", &ops);

        switch(ops)
        {
           case INSERT:
               printf("Enter the value to be added in the linked list\n");
               scanf("%d", &data); 
               ret = insertInLinkedList(&list, data);
               if(FAILURE == ret) {
                  printf("Error in inserting\n");                     
               } else {
                  printf("Node with value %d inserted successfully\n", data);
               }  
               break;

           case DELETE:
               printf("Enter the value to be deleted\n");
               scanf("%d", &data);
               ret = deleteFromLinkedList(&list, data); 
               if(FAILURE == ret) {
                  printf("Could not delete the node\n");
               }else {
                  printf("Node with value %d deleted successfully\n", data);               
               } 
               break;

           case SEARCH:
               printf("Enter the value to be searched\n");
               scanf("%d", &data);
               ret = searchInLinkedList(list, data); 
               if(FAILURE == ret) {
                  printf("Value %d not found in the list\n", data);
               }else {
                  printf("Node with value %d found in the list\n", data);               
               } 
               break;

           case PRINT:
               printf("Printing the entire linked list\n");
               ret = printLinkedList(list); 
               if(FAILURE == ret) {
                  printf("List is empty\n");
               }else {
                  printf("List printing done\n");               
               } 
               break;

            case EXIT:
               exitFromMainLoop = 1;
               break;

            default:
               break; 
        }
        if(exitFromMainLoop)
        {
           printf("Exiting from the main loop\n");
           break; 
        }
        printf("\n");
    }
}

