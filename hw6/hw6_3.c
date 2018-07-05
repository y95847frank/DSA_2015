#include<stdio.h>
#include<stdlib.h>
#include "avl_ntudsa.h"

int int_compare(const void *pa, const void *pb, void *param)
{
	int a = *(const int *)pa;
	int b = *(const int *)pb;
	
	if(a < b) return -1;
	else if ( a > b) return 1;
	else return 0;
}

void merge(struct avl_table *tree1, struct avl_node *tree2)
{
	int i;
	for(i = 0; i < tree2->avl_cnt; i++)
		avl_probe(tree1, tree2->avl_data);
	if(tree2->avl_link[0] != NULL)
		merge(tree1, tree2->avl_link[0]);
	if(tree2->avl_link[1] != NULL){
		merge(tree1, tree2->avl_link[1]);
	}
	return ;
}

int find(int *game, int num)
{
	if(game[num] == num){
		return num;
	}
	else 
		return find(game, game[num]);
}

void minus(struct avl_node *tree, long long int *money, int *count)
{
	if(tree == NULL)
		return ;
	if(*money >= tree->avl_sum[0]){
		*money -= tree->avl_sum[0];
		*count += tree->avl_cnode[0];
		if(*money / (tree->avl_data) > tree->avl_cnt) {
			*count += tree->avl_cnt;
			long long int tmp = tree->avl_cnt * tree->avl_data;
			*money -= tmp;
			minus(tree->avl_link[1], money, count);
		}
		else
			*count += *money / (tree->avl_data);
	}
	else
		minus(tree->avl_link[0], money, count);
}

int main()
{
int n, m, p;
scanf("%d %d", &n, &m);
int game[n + 1];
int i, j, k, command, num1, num2;
long long int money;
struct avl_table *tree[n + 1];
for(i = 0; i <= n; i++)
	tree[i] = avl_create(int_compare, NULL, NULL);

for(i = 1; i <= n; i++){
	scanf("%d", &p);
	int *q = avl_probe(tree[i], p);
}


for(k = 0; k < n; k++)
	game[k + 1] = k + 1;

for(j = 0; j < m; j++){
	scanf("%d", &command);
	if(command == 1){
		scanf("%d %d", &num1, &num2);
		int count1, count2;
		count1 = find(game, num1);
		count2 = find(game, num2);
		if(count1 == count2)
			continue;
		else {
			merge(tree[count1], tree[count2]->avl_root);
			game[count2] = count1;
		}
	}
	else if(command == 2){
		scanf("%d %lld", &num1, &money);
		int head = find(game, num1);
		printf("%d ", head);
		int kk = 0;
		minus(tree[head]->avl_root, &money, &kk);
		printf("%d\n", kk);
	}
}

return 0;
}
