#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int id_data;
	int grade_data;
	struct node *left;
	struct node *right;
} node;

node * insert(node *tree, int id, int grade) {
	if (tree == NULL) {
		node * root = (node*) malloc(sizeof(node));
		root->left = NULL;
		root->right = NULL;
		root->id_data = id;
		root->grade_data = grade;

		return root;
	} else {
		if (tree->grade_data < grade) {
			tree->right = insert(tree->right, id, grade);
			return tree;
		} else {
			tree->left = insert(tree->left, id, grade);
			return tree;
		}
	}
}

void inorder_Traversal(node *tree) {
	if (tree == NULL)
		return;
	inorder_Traversal(tree->left);
	printf("%d %d\n", tree->id_data, tree->grade_data);
	inorder_Traversal(tree->right);
}
void print_at_level(node *tree, int desired, int current) {

	if (tree) {
		if (desired == current)
			printf("%d %d", tree->id_data, tree->grade_data);
		else {

			print_at_level(tree->left, desired + 1, current);
			if (tree->left != NULL && current - 1 == desired)
				printf("(%d L)", tree->grade_data);
			print_at_level(tree->right, desired + 1, current);
			if (tree->right != NULL && current - 1 == desired)
				printf("(%d R)", tree->grade_data);

		}
	}

}
int height(node *tree){
	int leftheight, rightheight;
	if(tree==NULL)
	 return 0;
	else
	{
	 leftheight = height(tree ->left);
	 rightheight = height(tree->right);
	 if(leftheight > rightheight)
	 return (leftheight + 1);
	 else
	 return (rightheight + 1);
	}
}

int main(void) {
    node *head = NULL;
	int id,grade; scanf("%d %d",&id,&grade);
	while(id!=-1 && grade!=-1){
	    head=insert(head,id,grade);
		scanf("%d %d",&id,&grade);
}
    printf("\n");
    inorder_Traversal(head);
	int count;  count = height(head);
    printf("\n");
	int i;
	for (i = 0; i < count; ++i) {
		print_at_level(head,0,i);
		printf("\n");
}
}
