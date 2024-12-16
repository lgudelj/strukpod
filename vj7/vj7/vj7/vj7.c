#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

#define EMPTY_STACK 1
#define EXIT_SUCCESS 0
#define MALLOC_ERROR -1
#define SCANF_ERROR -2

struct direktorij;
typedef struct direktorij* DirektorijPozicija;
typedef struct direktorij {
	char ime[MAX_LENGTH];
	DirektorijPozicija poddirektorijPozicija;
	DirektorijPozicija next;
} Direktorij;

struct Stog;
typedef struct Stog* stogPozicija;
typedef struct Stog {
	DirektorijPozicija direktorijLevel;
	stogPozicija next;
} stog;

DirektorijPozicija napraviDir(char* imedirektorija);
int push(stogPozicija, DirektorijPozicija);
int pop(stogPozicija);
int dodajDir(DirektorijPozicija, DirektorijPozicija);
int promijeniDir(stogPozicija, char*);
int printDir(DirektorijPozicija, int);

int main()
{
	char input = 0;
	char ImeDir[MAX_LENGTH] = { 0 };
	Direktorij headDir = { .ime = {0}, .poddirektorijPozicija = NULL, .next = NULL };
	DirektorijPozicija rootDir = NULL;
	stog headStog = { .direktorijLevel = NULL, .next = NULL };

	rootDir = napraviDir("C:");
	if (rootDir == NULL) return MALLOC_ERROR;

	headDir.next = rootDir;
	push(&headStog, rootDir);

	printf("1 - napravi direktorij\n2 - promijeni direktorij u <dir>\n3 - idi do roditelja direktorija\n4 - pregled sadrzaja direktorija\n5 - zavrsi program\n");

	do {
		printf("Unesi komandu: ");
		if (scanf(" %c", &input) != 1) return SCANF_ERROR;

		switch (input) {
		case '1':
			// md - make directory
			printf("md ");
			if (scanf(" %s", ImeDir) != 1) return SCANF_ERROR;

			DirektorijPozicija noviDirektorij = napraviDir(ImeDir);
			if (noviDirektorij == NULL) return MALLOC_ERROR;
			dodajDir(headStog.next->direktorijLevel, noviDirektorij);
			printf("Napravljen direktorij %s\n", ImeDir);

			break;
		case '2':
			// cd <dir> - change directory
			printf("cd ");
			if (scanf(" %s", ImeDir) != 1) return SCANF_ERROR;
			promijeniDir(&headStog, ImeDir);
			break;
		case '3':
			// cd.. - go to parent directory
			if (pop(&headStog)) printf("Vec si u root direktoriju.\n");
			else printf("U roditeljskom direktoriju si \n");
			break;
		case '4':
			// dir - view directory content
			printf("Ispis sadrzaja %s:\n", headStog.next->direktorijLevel->ime);
			printDir(headStog.next->direktorijLevel, 0);
			break;
		case '5':
			// end of program
			printf("\n*Kraj programa.*\n");
			break;
		default:
			printf("Greska u inputu.\n");
			break;
		}

	} while (input != '5');


	izbrisiDir(&headDir);
	izbrisiStog(&headStog);

	return 0;
}

DirektorijPozicija napraviDir(char* dirIme) {

	DirektorijPozicija noviDir = NULL;
	noviDir = (DirektorijPozicija)malloc(sizeof(Direktorij));

	if (noviDir == NULL) return NULL;

	strcpy(noviDir->ime, dirIme);
	noviDir->poddirektorijPozicija = NULL;
	noviDir->next = NULL;

	return noviDir;
}

int push(stogPozicija headstog, DirektorijPozicija trenutniDir) {

	stogPozicija noviStog = NULL;
	noviStog = (stogPozicija)malloc(sizeof(stog));

	if (noviStog == NULL) return MALLOC_ERROR;

	noviStog->direktorijLevel = trenutniDir;

	noviStog->next = headstog->next;
	headstog->next = noviStog;

	return EXIT_SUCCESS;
}

int pop(stogPozicija headStog) {

	stogPozicija temp;

	if (headStog->next == NULL) return EMPTY_STACK; // Stog je prazan

	temp = headStog->next;
	headStog->next = headStog->next->next;
	free(temp);

	return 0;
}

int dodajDir(DirektorijPozicija superdir, DirektorijPozicija poddir) {

	poddir->next = superdir->poddirektorijPozicija;
	superdir->poddirektorijPozicija = poddir;

	return EXIT_SUCCESS;
}


int promijeniDir(stogPozicija headstog, char* imedir) {

	DirektorijPozicija trenutni = headstog->next->direktorijLevel->poddirektorijPozicija;

	while (trenutni != NULL && strcmp(trenutni->ime, imedir) != 0) trenutni = trenutni->next;

	if (trenutni != NULL) {
		printf("Promijenjen direktorij u %s\n", imedir);
		push(headstog, trenutni);
	}
	else printf("Direktorij nije pronaden.\n");

	return EXIT_SUCCESS;
}

int printDir(DirektorijPozicija trenutni, int visina) {

	int i = 0;
	DirektorijPozicija trenpoddir = NULL;

	if (trenutni->poddirektorijPozicija != NULL) {
		trenpoddir = trenutni->poddirektorijPozicija;
		while (trenpoddir != NULL) {
			for (i = 0; i < visina; i++)
				printf(" ");
			printf("%s\n", trenpoddir->ime);
			printDir(trenpoddir, visina + 1);
			trenpoddir = trenpoddir->next;
		}
	}

	return 0;
}

int izbrisiDir(DirektorijPozicija headDir) {

	DirektorijPozicija temp = NULL;

	while (headDir->next != NULL) {
		temp = headDir->next;
		headDir->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int izbrisiStog(stogPozicija headstog) {

	stogPozicija temp = NULL;

	while (headstog->next != NULL) {
		temp = headstog->next;
		headstog->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}