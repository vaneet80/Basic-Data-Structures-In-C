// Implement Doubly Linked List
// INSERT: O(n), DELETE: O(n), SEARCH: O(n)
// Can Traverse in both directions
// Given a node, it can be deleted 

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
   int data;
   struct node *next;
   struct node *prev;
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
}doublyLinkedListOps;

node *createNode(int data)
{
   node *newNode;

   newNode = (node *)(malloc(sizeof(node)));
   if(NULL == newNode)
   {
       printf("Memory allocation for the new node failed\n");
       return newNode;
   }
   newNode->next = NULL;
   newNode->prev = NULL;
   newNode->data = data;

   return newNode; 
}

status insertInDoublyLinkedList(node **list, int data)
{
   node *tempList;
   node *lastNode;
   node *newNode;

   newNode = createNode(data);
   if(NULL == newNode)
   {
       printf("Could not create a new node\n");
       return FAILURE; 
   }

   tempList = *list;

   // List is empty, insert in the head
   if(NULL == tempList)
   {
       *list = newNode;
       return SUCCESS;   
   } 

   while(tempList != NULL)
   {
       lastNode = tempList;
       tempList = tempList->next;
   }

   lastNode->next = newNode;
   newNode->prev = lastNode;
 
   return SUCCESS;
}

status deleteFromDoublyLinkedList(node **list, int data)
{
   node *prevNode;
   node *currNode;

   if(NULL == *list)
   {
       printf("Double linked list is empty, can not delete\n");
       return FAILURE;
   }
   if((*list)->data == data)
   {
       *list = (*list)->next;
       if(*list != NULL)
          (*list)->prev = NULL;
       return SUCCESS;
   }

   currNode = *list; 
   while(currNode != NULL)
   {
       if(data == currNode->data)
       {
           prevNode->next = currNode->next;
           currNode = currNode->next;
           if(NULL != currNode)
           { 
              currNode->prev = prevNode;
           }
           return SUCCESS;
       }  
       prevNode = currNode;
       currNode = currNode->next;
   } 

   return FAILURE;
}

status printDoublyLinkedList(node *list)
{
    if(NULL == list)
    {
        printf("List is empty\n");
        return FAILURE;
    }   

    while(list != NULL)
    {
        printf("%d ->", list->data);
        list = list->next;
    }

    printf("\n");
    return SUCCESS;    
}

status searchInDoublyLinkedList(node *list, int data)
{
   if(NULL == list)
   {
       printf("Linked list is empty\n");
       return FAILURE;
   }  

   while(list != NULL)
   {
       if(data == list->data)
       {
           printf("Node with value %d found\n", data);
           return SUCCESS; 
       } 
       list = list->next;
   }

   return FAILURE;
}

int main()
{
    int ops;
    int data; 
    int ret=SUCCESS;
    node *list;
    int exitFromMainLoop = 0;

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
               ret = insertInDoublyLinkedList(&list, data);
               if(FAILURE == ret) {
                  printf("Error in inserting\n");                     
               } else {
                  printf("Node with value %d inserted successfully\n", data);
               }  
               break;

           case DELETE:
               printf("Enter the value to be deleted\n");
               scanf("%d", &data);
               ret = deleteFromDoublyLinkedList(&list, data); 
               if(FAILURE == ret) {
                  printf("Error in deleting the node\n");
               }else {
                  printf("Node with value %d deleted successfully\n");               
               } 
               break;

           case SEARCH:
               printf("Enter the value to be searched\n");
               scanf("%d", &data);
               ret = searchInDoublyLinkedList(list, data); 
               if(FAILURE == ret) {
                  printf("Error in searching the node\n");
               }else {
                  printf("Node with value %d found in the list\n");               
               } 
               break;

           case PRINT:
               printf("Printing the entire linked list\n");
               ret = printDoublyLinkedList(list); 
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







