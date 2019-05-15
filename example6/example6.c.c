#include<stdio.h> 
#include<stdlib.h> 

typedef struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
    int balance;
}Node; 

int max(int a, int b); 
  

int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  

struct Node* newNode(int key) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  
    return(node); 
} 
  
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
   
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
   
    return x; 
} 

struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    
    y->left = x; 
    x->right = T2; 
  
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    
    return y; 
} 
  

int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  

struct Node* insert(struct Node* node, int key) 
{ 
   
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else 
        return node; 
  
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
 
    int balance = getBalance(node); 
  
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 

    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
   
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    return node; 
} 
void inOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        
        inOrder(root->left); 
        printf("%d\n", root->key); 
        inOrder(root->right); 
    } 
} 
void print_at_level(Node *tree, int desired, int current) {

	if (tree) {
		if (desired == current){
            if(desired==0)
			printf("%d (%d B)", tree->key,getBalance(tree));
            else
            printf("%d", tree->key);

        }
            
		else {

			print_at_level(tree->left, desired + 1, current);
			if (tree->left != NULL && current - 1 == desired)
				printf(" (%d L) (%d B) ", tree->key,getBalance(tree->left));
			print_at_level(tree->right, desired + 1, current);
			if (tree->right != NULL && current - 1 == desired)
				printf(" (%d R) (%d B) ", tree->key,getBalance(tree->right));

		}
	}

}

int main() 
{ 
  struct Node *root = NULL; 
  int key; scanf("%d",&key);
  while(key!=-1){
      root=insert(root,key);
      scanf("%d",&key);
  }

  
  inOrder(root); 

      printf("\n");
	int i;
	for (i = 0; i < root->height; ++i) {
		print_at_level(root,0,i);
		printf("\n");
}
  
  return 0; 
} 