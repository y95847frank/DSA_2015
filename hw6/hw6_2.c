#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

void preorder_integer_avl ( const struct avl_node *node )
{
	int i;
	if ( node == NULL)
		return ;
	char str[128];
	strcpy(str, node->avl_data);
	for(i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf(" ");
	//printf("%c ", *((char *)node->avl_data));
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
		putchar('(');
		preorder_integer_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_avl(node->avl_link[1]);
		putchar(')');
	}
}

void preorder_integer_bst ( const struct bst_node *node )
{
	int i;
	if ( node == NULL)
		return ;
	char str[128];
	strcpy(str, node->bst_data);
	for(i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf(" ");
	//printf("%c ", *((char *)node->avl_data));
	if(node->bst_link[0] != NULL || node->bst_link[1] != NULL){
		putchar('(');
		preorder_integer_bst(node->bst_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_bst(node->bst_link[1]);
		putchar(')');
	}
}
void preorder_integer_rb ( const struct rb_node *node )
{
	int i;
	if ( node == NULL)
		return ;
	char str[128];
	strcpy(str, node->rb_data);
	for(i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf(" ");
	//printf("%c ", *((char *)node->avl_data));
	if(node->rb_link[0] != NULL || node->rb_link[1] != NULL){
		putchar('(');
		preorder_integer_rb(node->rb_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_rb(node->rb_link[1]);
		putchar(')');
	}
}

int int_compare(const void *pa, const void *pb, void *param)
{
	char *a = (char *) pa;
	char *b = (char *) pb;
	
	return strcmp(a, b);
}

int main()
{
struct avl_table *tree;
struct bst_table *tree2;
struct rb_table *tree3;

tree = avl_create(int_compare, NULL, NULL);
tree2 = bst_create(int_compare, NULL, NULL);
tree3 = rb_create(int_compare, NULL, NULL);

char str[128];
int i;
for(i = 0; i < 32; i++){
	scanf("%s", str);
	char *element = (char *)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(element, str);
	void **p = avl_probe(tree, element);
	void **q = bst_probe(tree2, element);
	void **r = rb_probe(tree3, element);
}

preorder_integer_avl(tree->avl_root);
puts("");
preorder_integer_bst(tree2->bst_root);
puts("");
preorder_integer_rb(tree3->rb_root);
puts("");

return 0;
}
