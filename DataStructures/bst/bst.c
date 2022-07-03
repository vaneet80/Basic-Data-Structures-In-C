#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

// Implement Binary Search Tree
// Insert: O(height), Delete: O(height), Search: O(height)
// Inorder, Preorder and Postorder traversal
// If BST is balanced (e.g. Red-Black tree, AVL tree)
// Then height is logn and operations can be done in logn time

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

typedef enum{
    INSERT=0,
    DELETE,
    SEARCH,
    PRINT,
    EXIT 
}bstOps;

typedef enum{
    INORDER=0,
    PREORDER,
    POSTORDER
}bstTraversal;

typedef enum{
    SUCCESS=0,
    FAILURE 
}status;

node* createNode(int value)
{
    node *newNode;

    newNode = (node *)(malloc(sizeof(node)));
    if(NULL == newNode)
    {
        printf("Error is memory allocation\n");
        return newNode;
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
status insertInBst(node **bst, int value)
{
    node *newNode;
    node *myBst;
    node *prev;
    uint8_t isLeft=0;    

    newNode = createNode(value);
    if(NULL == newNode)
    { 
        printf("Could not create a new node\n");
        return FAILURE; 
    } 

    if(NULL == *bst) // This is the first element to be inserted
    {
        *bst = newNode;
        return SUCCESS;
    }
    
    myBst = *bst;

    while(myBst != NULL) {
         prev = myBst;
         if(value < myBst->data) {
             myBst = myBst->left;
             isLeft = 1;             
         }else{
             myBst = myBst->right;             
             isLeft = 0;
         }    
    }
    
    if(isLeft){
        prev->left = newNode;
    }else{
        prev->right = newNode;
    }
    
    return SUCCESS;
}

node *findPredecessor(node *bst)
{
    node *prev;
    int isLeft=1;
     
    prev = bst;
    bst = bst->left;

    while(bst->right != NULL) {
       prev = bst;
       bst = bst->right;
       isLeft = 0;
 
   }  

   if(isLeft)
      prev->left = NULL;
   else
      prev->right = NULL;

   return bst;
}
 
status deleteFromBst(node **bst, int value)
{
    node *myBst;
    node *prev=NULL;
    node *temp;
    node *predecessor;
    uint8_t isLeft=0;

    // Check if BST is empty 
    if(NULL == *bst){
        printf("BST is empty\n");
        return FAILURE;
    }

    myBst = *bst;
    while(NULL != myBst)
    {      
        if(value == myBst->data)
        {
            break;
        }else if(value < myBst->data) {
             prev = myBst;
             myBst = myBst->left;
             isLeft = 1;
        }else {
             prev = myBst;
             myBst = myBst->right;          
        } 
    }

    if(NULL == myBst){
        printf("Element with value %d not found\n", value);
        return FAILURE;
    } else if(NULL == myBst->left && NULL == myBst->right) { // Node with no children to be deleted
        if(NULL == prev){ // Root node to be deleted
            temp = *bst;
            *bst = NULL;
            free(temp);
        } else {
            if(isLeft){ 
              prev->left = NULL;
              free(myBst);
            }else{
              prev->right = NULL;
              free(myBst);  
            }
        }
        return SUCCESS; 
    }else if(NULL == myBst->left && myBst->right != NULL) {// Node with only right child to be deleted
        if(NULL == prev){
            temp = *bst; 
            *bst = myBst->right;
            free(temp); 
        }else{
            if(isLeft){
                prev->left = myBst->right;
                free(myBst);
            }else{
                prev->right = myBst->right;
                free(myBst);  
            }
        }
        return SUCCESS;
    }else if(NULL == myBst->right && myBst->left != NULL){ //Node with only left child to be deleted 
        if(NULL == prev){
            temp = *bst; 
            *bst = myBst->left;
            free(temp); 
        }else{
            if(isLeft){
                prev->left = myBst->left;
                free(myBst);
            }else{
                prev->right = myBst->left;
                free(myBst);  
            }
        }
        return SUCCESS;   
    } else { // Node has both right and left subtrees
        printf("Node to be deleted has both left and right children\n"); 
        predecessor = findPredecessor(myBst);
        predecessor->left = myBst->left;
        predecessor->right = myBst->right;
        if(NULL == prev){ 
           *bst = predecessor;
           free(myBst); 
        }else{
           if(isLeft) {
              prev->left = predecessor;
              free(myBst);
           }else {
              prev->right = predecessor;
              free(myBst);
           } 
        }
        return SUCCESS;   
    }
}

status searchInBst(node *bst, int data)
{
    if(NULL == bst) {
       printf("Search failed\n");
       return FAILURE;
    }

    while(bst != NULL) {
       if(data == bst->data) {
          return SUCCESS;
       }else if(data < bst->data) {
          bst = bst->left;
       }else {
          bst = bst->right;
       }
    }

    return FAILURE;
}


void printInorder(node *bst)
{
   if(NULL == bst)
      return;

   printInorder(bst->left);
   printf("%d ", bst->data);
   printInorder(bst->right);
} 

void printPreorder(node *bst)
{
   if(NULL == bst)
      return;

   printf("%d ", bst->data);
   printInorder(bst->left);
   printInorder(bst->right);
}

 
void printPostorder(node *bst)
{
   if(NULL == bst)
      return;

   printInorder(bst->left);
   printInorder(bst->right);
   printf("%d ", bst->data);
}
 
int main()
{
   node *bst=NULL;
   int ops;
   int data;
   int traversalType;
   int exitFromLoop=0;
   status ret;

   while(1){
      printf("Enter the operation\n");
      printf("INSERT:0, DELETE:1, SEARCH:2, PRINT:3, EXIT:4\n");
      scanf("%d", &ops);

      switch(ops){
         case INSERT:
             printf("Enter the element to be inserted\n");
             scanf("%d", &data);
             ret = insertInBst(&bst, data);
             if(FAILURE == ret){
                printf("Error in inserting %d in the BST\n", data);
             }else{
                printf("Element %d inserted in the BST successfully\n", data);
             }
             break;

         case DELETE:
             printf("Enter the element to be deleted\n");
             scanf("%d", &data);
             ret = deleteFromBst(&bst, data);
             if(FAILURE == ret){
                printf("Error in deleting the element %d\n", data);
             }else{
                printf("Element %d deleted successfully\n", data);
             }
             break;

         case SEARCH:
             printf("Enter the element to be searched\n");
             scanf("%d", &data);
             ret = searchInBst(bst, data);
             if(FAILURE == ret) {
                printf("Element %d not found in the BST\n", data);
             }else{
                printf("Element %d found in the BSR\n", data);
             }
             break;

          case PRINT:
             printf("Enter the type of the traversal \n");
             printf("INORDER:0, PREORDER:1, POSTORDER:2\n");
             scanf("%d", &traversalType);  
             switch(traversalType) {
                  case INORDER:
                       printInorder(bst);
                       break;

                  case PREORDER:
                       printPreorder(bst);
                       break;

                  case POSTORDER:
                       printPostorder(bst);
                       break;

                  default:
                       break;   
             } 
             break;

          case EXIT:
             exitFromLoop = 1;
             break;

          default:
             break;     
      }
      if(exitFromLoop)
          break; 
   }
}
