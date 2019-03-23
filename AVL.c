
/*******************************************************************************
*
*                   Implementação AVL (balanced trees)
*                       Autor: Gabriel Matheus
*                          github.com/gmsj
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int hc = 0;

typedef struct bt {
	int val; // Valor do nó
	int bf; // Balance factor dado que bf(n) = (subArvores à esquerda) - (subArvores à direita)
	struct bt *left;
	struct bt *right;
} bt;

void visit (bt *root) { // Acao desejada no node, nesse caso, apenas mostrar o valor
	printf("Val Node: %d\n", root->val);
}

void preOrder (bt *root) {
	if (root == NULL) {
		return;
	}
	visit(root);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder (bt *root) {
	if (root == NULL) {
		return;
	}
	inOrder(root->left);
	visit(root);
	inOrder(root->right);
}

void posOrder (bt *root) {
	if (root == NULL) {
		return;
	}
	posOrder(root->left);
	posOrder(root->right);
	visit(root);
}

int height (bt *root) { // Retorna a altura total da árvore
	int h1, h2;
	if (root == NULL) {
		return 0;
	}
	h1 = height(root->left);
	h2 = height(root->right);
	if (h1 > h2) {
		return (h1 + 1);
	}
	else {
		return(h2 + 1);
	}
}

bt *avlRotateleft (bt *root) {
	bt *r, *rl;
	r = root->right;
	rl = root->right->left;
	r->left = root;
	root->right = rl;
	if (r->bf >= 0) {
		root->bf = ((root->bf)-1)-(r->bf);
	}
	else {
		root->bf = (root->bf)-1;
	}
	if (root->bf < 0) {
		r->bf = ((r->bf)-1) + (root->bf);
	}
	else {
		r->bf = (r->bf)-1;
	}
	return r;
}

bt *avlRotateRight (bt *root) {
	bt *r, *rl;
	r = root->left;
	rl = root->left->right;
	r->right = root;
	root->left = rl;
	if (r->bf >= 0) {
		root->bf = ((root->bf)-1)+(r->bf);
	}
	else {
		root->bf = (root->bf)+1;
	}
	if (root->bf < 0) {
		r->bf = ((r->bf)-1) - (root->bf);
	}
	else {
		r->bf = (r->bf)+1;
	}
	return r;
}

bt *avlInsert (bt *root, int v) {
	if (root == NULL) {
		bt *n = (bt*) calloc (1,sizeof(bt));
		n->left = n->right = NULL;
		n->val = v;
		n->bf = 0;
		hc = 1;
		return n;
	}
	else if (root->val == v) {
		hc = 0;
		return root;
	}
	else if (v < root->val) {
		root->left = avlInsert(root->left, v);
		root->bf = (root->bf) - hc;
	}
	else {
		root->right = avlInsert(root->right, v);
		root->bf = (root->bf) + hc;
	}
	if (!hc) {
		return root;
	}
	else if (root->bf == 0) {
		hc = 0;
		return root;
	}
	else if (root->bf == 1 || root->bf == -1) {
		hc = 1;
		return  root;
	}
	else if (root->bf == -2) {
		if (root->left->bf == 1) {
			root->left = avlRotateleft(root->left);
		}
		hc = 0;
		return (avlRotateRight(root));
	}
	else if (root->bf == 2) {
		if (root->right->bf == -1) {
			root->right = avlRotateRight(root->right);
		}
		hc = 0;
		return (avlRotateleft(root));
	}
}

void clear (bt *root) { // Liberar o espaço usado, percurso similar ao inOrder	
	if (root == NULL) {
		return;
	}
	else {
		clear(root->left);
		free(root->left);
		clear(root->right);
		free(root->right);
	}
}

int main () {
	int i, v, tam;
	bt *root = NULL;
	printf("Digite o tamanho da arvore (Qtd de eltos):\n");
	scanf("%d", &tam);
	for (i = 0; i < tam; i++) {
		scanf("%d", &v);
		root = avlInsert(root, v);
	}
	printf("Listando os elementos...\n");
	printf("Em preOrdem\n");
	preOrder(root);
	printf("Em Ordem\n");
	inOrder(root);
	printf("Pos ordem\n");
	posOrder(root);
	printf("A altura final da BST eh: %d\n", height(root));
	clear(root);
	free(root); // liberar a raiz
	return 0;
}