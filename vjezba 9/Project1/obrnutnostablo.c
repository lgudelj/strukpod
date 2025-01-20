#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct CvorStabla* Stablo;
typedef struct CvorStabla {
	int El;	
	Stablo L;
	Stablo D;
}stablo;

Stablo unos(Stablo, int);
Stablo pretrazi(int, Stablo);
Stablo izbElement(Stablo, int);
Stablo nadiMin(Stablo);
Stablo suma(Stablo);
void printstablo(Stablo);
void PrintPreorder(Stablo);
void PrintPostorder(Stablo);
void PrintInorder(Stablo);
void levelOrder(Stablo);
void izbStablo(Stablo);
int replace(Stablo);
void writeTreeToFile(FILE*, Stablo);

int main()
{
	Stablo root = NULL;
	Stablo roott = NULL;
	int broj, trazi;
	Stablo rez;
	srand(time(NULL));
	FILE* file = fopen("stabla.txt", "w");
	if (file == NULL) {
		printf("Greška prilikom otvaranja datoteke");
		return 0;
	}

	root = unos(root, 2);
	root = unos(root, 5);
	root = unos(root, 7);
	root = unos(root, 8);
	root = unos(root, 11);
	root = unos(root, 1);
	root = unos(root, 4);
	root = unos(root, 2);
	root = unos(root, 3);
	root = unos(root, 7);
	fprintf(file, "Obrnuto stablo\n");
	writeTreeToFile(file, root);
	fprintf(file, "\n");
	printstablo(root);
	printf("nakon replacea");
	replace(root);
	printstablo(root);
	fprintf(file, "Replace stablo\n");
	writeTreeToFile(file, root);
	fprintf(file, "\n");

	printf("Nasumicno \n");
	int i;
	for (i = 0;i < 9;i++)
	{
		roott = unos(roott, (rand() % 80) + 10);
	}
	printstablo(roott);
	fprintf(file, "Nasumicno stablo\n");
	writeTreeToFile(file, roott);
	fprintf(file, "\n");
	fclose(file);
	izbStablo(root);
	izbStablo(roott);
	return 0;
}

Stablo unos(Stablo root, int broj)
{
	if (!root)
	{
		root = (Stablo)malloc(sizeof(stablo));
		if (!root)
			return NULL;
		root->El = broj;
		root->L = NULL;
		root->D = NULL;
	}
	else if (broj >= root->El)
	{
		root->L = unos(root->L, broj);
	}
	else if (broj < root->El)
	{
		root->D = unos(root->D, broj);
	}
	return root;
}
void printstablo(Stablo root)
{
	printf("\nPreorder\n");
	PrintPreorder(root);
	printf("\nInorder\n");
	PrintInorder(root);
	printf("\nPostorder\n");
	PrintPostorder(root);
	printf("\nPrint level order\n");
	levelOrder(root);
}
void PrintPreorder(Stablo root)
{
	if (!root)return;

	printf("%d\n", root->El);
	PrintPreorder(root->L);
	PrintPreorder(root->D);
}
void PrintPostorder(Stablo root)
{
	if (!root)return;

	PrintPreorder(root->L);
	PrintPreorder(root->D);
	printf("%d\n", root->El);
}
void PrintInorder(Stablo root) {
	if (!root)return;
	PrintInorder(root->L);
	printf("%d\n", root->El);
	PrintInorder(root->D);
}
void levelOrder(Stablo root)
{
	if (root == NULL) return;

	Stablo* red = (Stablo*)malloc(100 * sizeof(Stablo));
	int prednji = 0, zadnji = 0;

	red[zadnji++] = root;

	while (prednji < zadnji) {
		Stablo tren = red[prednji++];
		printf("%d\n", tren->El);

		if (tren->L != NULL) {
			red[zadnji++] = tren->L;
		}
		if (tren->D != NULL) {
			red[zadnji++] = tren->D;
		}
	}

	free(red);
}
Stablo pretrazi(int x, Stablo root) {
	if (!root) {
		return NULL;
	}
	else if (x < root->El) {
		return pretrazi(x, root->L);
	}
	else if (x > root->El) {
		return pretrazi(x, root->D);
	}


	return root;
}
Stablo izbElement(Stablo root, int x) {
	if (!root)return NULL;

	else if (x < root->El) {
		root->L = izbElement(root->L, x);
	}
	else if (x > root->El) {
		root->D = izbElement(root->D, x);
	}
	//ako pronađen element ima dvoje djece
	else if (root->L && root->D) {
		Stablo minD = nadiMin(root->D);
		root->El = minD->El;
		root->D = izbElement(root->D, minD->El);
	}
	else {
		Stablo temp = root;
		if (!root->L) { //ima samo desno dijete
			root = root->D;
		}
		else if (!root->D) {
			root = root->L;
		}
		else {
			root = NULL;
		}

		free(temp);
	}

	return root;
}
Stablo nadiMin(Stablo root) {
	if (!root->L)return root;
	return nadiMin(root->L);
}

void izbStablo(Stablo root) {
	if (!root)return;

	izbStablo(root->L);
	izbStablo(root->D);
	free(root);
}
int replace(Stablo node) {
	if (node == NULL) {
		return 0;
	}

	// Rekurzivno pozivamo lijevo i desno podstablo
	int left_sum = replace(node->L);
	int right_sum = replace(node->D);

	// Spremamo trenutnu vrijednost čvora
	int current_value = node->El;

	// Zamjenjujemo trenutnu vrijednost sa sumom lijevog i desnog podstabla
	node->El = left_sum + right_sum;

	// Vraćamo sumu koja uključuje trenutni čvor
	return current_value + node->El;
}
void writeTreeToFile(FILE* file, Stablo root) {
	if (!root)return;
	
	writeTreeToFile(file, root->L);
	fprintf(file, "%d ", root->El);
	writeTreeToFile(file, root->D);
	
}