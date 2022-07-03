#include<stdio.h>
#include<stdlib.h>

// Implement Hash Table Using Linked Lists
// Insert: O(1), Search: O(1), Delete: O(1)
// Hash table performance depends upon the distribution done by the hash function
// and number of hash buckets used. If the hash function is not crypytographic then 
// it is always possible to have a pathological dataset which makes the hash table
// performance bad. In such a case the solution is to use Uinversal family of hash
// functions. If uniformly at random a hash function is picked at the run time then
// perfomance is gauranteed to be good.

#define NO_BUCKETS  255

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
   EXIT 
}hashOperations;

typedef struct node
{
    int data;
    struct node *next;
}node;

node *createNode(int data)
{
    node *newNode;

    newNode = (node *)(malloc(sizeof(node)));
    if(NULL == newNode)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->next = NULL;

    newNode->data = data;

    return newNode;
}

status insertInHashTable(node **hT, int data)
{
    int hashIndex;
    node *list;
    node *last;

    hashIndex = data%NO_BUCKETS;
    list = hT[hashIndex]; 
    if(NULL == list)
    {
        hT[hashIndex] = createNode(data);
        return SUCCESS;
    }

    while(list != NULL)
    {
        if(list->data == data)
        {
            printf("Entry already exists\n");
            return FAILURE; 
        }
        last = list; 
        list = list->next;
    }

    last->next = createNode(data);
     
    return SUCCESS;        
}

status searchInHashTable(node **hT, int data)
{
    int hashIndex;
    node *list;

    hashIndex = data%NO_BUCKETS;

    list = hT[hashIndex];
    if(NULL == hT[hashIndex])
    {
        printf("Entry not found in the hash table\n");
        return FAILURE; 
    }

    while(list != NULL)
    {
        if(list->data == data)
        {
            return SUCCESS;
        }
        list = list->next;
    }
    
    return FAILURE;
}

status deleteFromHashTable(node **hT, int data)
{
    int hashIndex;
    node *list;
    node *prev;
    
    hashIndex = data%NO_BUCKETS;
    list = hT[hashIndex];
 
    if(NULL == list)
    {
        printf("Entry not found, can not delete\n");
        return FAILURE;
    } 

    if(data == list->data)
    {
        hT[hashIndex] = list->next;
        free(list);
        printf("Deleted the node\n"); 
        return SUCCESS;
    }

    prev = list;
    list = list->next;

    while(list != NULL)
    {
        if(list->data == data)
        {
            prev->next = list->next;
            free(list);
            return SUCCESS;
        } 
 
        prev = list;
        list = list->next;
    } 
  
    return FAILURE;
}

int main()
{
    int ops;
    int data;
    int exitFromMainLoop=0;
    status ret;
    node *hashTable[NO_BUCKETS]={NULL};

    while(1)
    {
        printf("Enter the operation\n");
        printf("Insert:0, Delete:1, Search:2,  Exit:3\n");
        scanf("%d", &ops);

        switch(ops) {
             case INSERT:
                 printf("Enter the value to be inserted\n");
                 scanf("%d", &data);
                 ret = insertInHashTable(hashTable, data);
                 if(FAILURE == ret)
                 {
                    printf("Can not insert in the hash table, entry already exists\n", data);
                 }else {
                    printf("Inserted %d successfully in the hash table\n", data);
                 }
                 break;

             case DELETE:
                 printf("Enter the value to be deleted\n");
                 scanf("%d", &data);
                 ret = deleteFromHashTable(hashTable, data);
                 if(FAILURE == ret)
                 {
                     printf("Could not delete from the hash Table, entry not found\n");
                 }else { 
                     printf("Deleted %d successfully in the hash table\n", data);
                 }
                 break;

             case SEARCH:
                 printf("Enter the value to be searched\n");
                 scanf("%d", &data);
                 ret = searchInHashTable(hashTable, data);
                 if(FAILURE == ret)
                 {
                     printf("Search failed, entry not found\n");
                 }else{
                     printf("Value %d found in the hash table\n", data);
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
            break;
        }  
        printf("\n"); 
    }
}
