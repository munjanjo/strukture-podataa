#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _stablo stablo;
typedef stablo* pozicija;
struct _stablo {
	int el;
	pozicija left;
	pozicija right;
};
pozicija addElIntoTree(pozicija, int);
pozicija insert(pozicija, int);
int printAll(pozicija);
int replace(pozicija);
int zbroji(pozicija);
int main() {
	int br[10]={2,5,7,8,11,1,4,2,3,7};
	pozicija root = NULL;
	root = (pozicija)malloc(sizeof(stablo));
	root->right = NULL;
	root->left = NULL;
	if (!root) {
		printf("krivo allocirana memorija!\n");
		return 0;
	}
	for (int i = 0; i < 10; i++) {
		root = insert(root, br[i]);
	}
	printAll(root);
	replace(root);
	printf("\n");
	printAll(root);
	return 0;
}
pozicija insert(pozicija root, int x) {
	if (root == NULL) {
		root->el = x;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (root->el > x) {
		root->right = addElIntoTree(root->right, x);
	}
	else if (root->el<=x)
		root->left = addElIntoTree(root->left, x);
	return root;



}
pozicija addElIntoTree(pozicija p, int el) {
	if (p == NULL)
	{
		p = (pozicija)malloc(sizeof(stablo));
		if (p == NULL)
		{
			printf("krivo aloc memorija!\n");
			return 0;
		}
		p->el = el;
		p->right = NULL;
		p->left = NULL;
	}
	else if (p->el > el)
		p->right = addElIntoTree(p->right, el);
	else if(p->el <= el)
		p->left = addElIntoTree(p->left, el);

	return p;
}
int printAll(pozicija root) {
	if (root == NULL)
		return 0;
	printAll(root->left);
	printf("%d ", root->el);
	printAll(root->right);
	return 0;
}
int replace(pozicija p)
{
	if (!p)
		return 0;
	p->el = zbroji(p->left) + zbroji(p->right);
	replace(p->left);
	replace(p->right);

	return 0;
}
int zbroji(pozicija p) {
	if (!p)
		return 0;
	else
		return(p->el + zbroji(p->left) + zbroji(p->right));

}