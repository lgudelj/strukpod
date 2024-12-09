#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

#define EXIT_SUCCESS 0
#define FILE_OPEN_ERROR -1
#define MALLOC_ERROR -2
#define SCANF_ERROR -3

struct artikl;
typedef struct artikl* PozicijaArtikla;
typedef struct artikl {
    char naziv[20];
    int kolicina;
    int cijena;
    PozicijaArtikla sljedeci;
} Artikl;

struct racun;
typedef struct racun* PozicijaRacuna;
typedef struct racun {
    char datum[10];
    Artikl glavaArtikla;
    PozicijaRacuna sljedeci;
} Racun;

int dodajArtikl(PozicijaArtikla glava, PozicijaArtikla artikl);
int dodajRacun(PozicijaRacuna glava, PozicijaRacuna racun);
int procitajRacun(char* imeDatoteke, PozicijaRacuna glavaRacuna);
int ispisiArtikle(PozicijaArtikla artikl);
int ispisiRacune(PozicijaRacuna racun);
int dohvatiArtiklUVremenu(PozicijaRacuna trenutniRacun, char* artikl, char* pocetniDatum, char* krajnjiDatum, int* prihod, int* broj);
int izbrisiArtikle(PozicijaArtikla glavaArtikla);
int izbrisiRacune(PozicijaRacuna glavaRacuna);

int main()
{
    int prihod = 0, broj = 0;
    char artikl[100] = { 0 };
    char pocetniDatum[20] = { 0 }, krajnjiDatum[20] = { 0 };
    char trenutniRacun[MAX_LINE] = { 0 };
    FILE* datotekaPointer = NULL;
    Racun glavaRacuna = {
        .datum = {0},
        .glavaArtikla = NULL,
        .sljedeci = NULL
    };

    datotekaPointer = fopen("racuni.txt", "r");
    if (datotekaPointer == NULL) {
        printf("Datoteka se ne može otvoriti.\n");
        return FILE_OPEN_ERROR;
    }

    while (!feof(datotekaPointer)) {
        fgets(trenutniRacun, MAX_LINE, datotekaPointer);
        trenutniRacun[strcspn(trenutniRacun, "\n")] = 0; // Uklanja '\n'
        printf("%s\n", trenutniRacun);
        procitajRacun(trenutniRacun, &glavaRacuna);
    }

    ispisiRacune(glavaRacuna.sljedeci);

    printf("\nUnesite naziv artikla: ");
    if (scanf("%s", artikl) != 1) return SCANF_ERROR;
    printf("Unesite pocetni datum (YYYY-MM-DD): ");
    if (scanf("%s", pocetniDatum) != 1) return SCANF_ERROR;
    printf("Unesite krajnji datum (YYYY-MM-DD): ");
    if (scanf("%s", krajnjiDatum) != 1) return SCANF_ERROR;

    dohvatiArtiklUVremenu(&glavaRacuna, artikl, pocetniDatum, krajnjiDatum, &prihod, &broj);
    printf("Prihod od %d %s: %d\n", broj, artikl, prihod);

    izbrisiRacune(&glavaRacuna);
    fclose(datotekaPointer);

    return 0;
}

int dodajArtikl(PozicijaArtikla glava, PozicijaArtikla artikl)
{
    PozicijaArtikla trenutni = glava;

    while (trenutni->sljedeci != NULL && strcmp(trenutni->sljedeci->naziv, artikl->naziv) == -1)
        trenutni = trenutni->sljedeci;

    artikl->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = artikl;

    return 0;
}

int dodajRacun(PozicijaRacuna glava, PozicijaRacuna racun)
{
    PozicijaRacuna trenutni = glava;

    while (trenutni->sljedeci != NULL && strcmp(trenutni->sljedeci->datum, racun->datum) <= 0)
        trenutni = trenutni->sljedeci;

    racun->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = racun;

    return 0;
}

int procitajRacun(char* imeDatoteke, PozicijaRacuna glavaRacuna)
{
    char datumString[20] = { 0 };
    char artiklString[MAX_LINE] = { 0 };
    FILE* datotekaPointer = NULL;
    PozicijaRacuna noviRacun = NULL;
    PozicijaArtikla noviArtikl = NULL;

    datotekaPointer = fopen(imeDatoteke, "r");
    if (datotekaPointer == NULL) {
        printf("Datoteka se ne može otvoriti.\n");
        return FILE_OPEN_ERROR;
    }

    noviRacun = (PozicijaRacuna)malloc(sizeof(Racun));
    if (noviRacun == NULL) {
        printf("Greška pri alokaciji memorije.\n");
        return MALLOC_ERROR;
    }

    fgets(datumString, 20, datotekaPointer);
    datumString[strcspn(datumString, "\n")] = 0;

    strcpy(noviRacun->datum, datumString);
    noviRacun->glavaArtikla.sljedeci = NULL;

    while (!feof(datotekaPointer))
    {
        noviArtikl = (PozicijaArtikla)malloc(sizeof(Artikl));
        if (noviArtikl == NULL) {
            printf("Greška pri alokaciji memorije.\n");
            return MALLOC_ERROR;
        }

        if (fscanf(datotekaPointer, "%[^,], %d, %d ",
            noviArtikl->naziv, &noviArtikl->kolicina, &noviArtikl->cijena) != 3) {
            printf("Greška pri unosu podataka.\n");
            return SCANF_ERROR;
        }

        dodajArtikl(&noviRacun->glavaArtikla, noviArtikl);
    }

    dodajRacun(glavaRacuna, noviRacun);

    fclose(datotekaPointer);

    return 0;
}

int ispisiArtikle(PozicijaArtikla trenutni)
{
    while (trenutni != NULL) {
        printf("\t%s, %d, %d\n", trenutni->naziv, trenutni->kolicina, trenutni->cijena);
        trenutni = trenutni->sljedeci;
    }

    return 0;
}

int ispisiRacune(PozicijaRacuna trenutni)
{
    while (trenutni != NULL) {
        printf("Racun od datuma %s:\n", trenutni->datum);
        ispisiArtikle(trenutni->glavaArtikla.sljedeci);
        trenutni = trenutni->sljedeci;
    }

    return 0;
}

int dohvatiArtiklUVremenu(PozicijaRacuna trenutniRacun, char* artikl, char* pocetniDatum, char* krajnjiDatum, int* prihod, int* broj)
{
    PozicijaArtikla trenutniArtikl = NULL;

    while (trenutniRacun != NULL && strcmp(trenutniRacun->datum, pocetniDatum) == -1)
        trenutniRacun = trenutniRacun->sljedeci;

    while (trenutniRacun != NULL && strcmp(trenutniRacun->datum, krajnjiDatum) <= 0) {
        trenutniArtikl = trenutniRacun->glavaArtikla.sljedeci;
        while (trenutniArtikl != NULL) {
            if (strcmp(trenutniArtikl->naziv, artikl) == 0) {
                *prihod += trenutniArtikl->kolicina * trenutniArtikl->cijena;
                *broj += trenutniArtikl->kolicina;
            }
            trenutniArtikl = trenutniArtikl->sljedeci;
        }
        trenutniRacun = trenutniRacun->sljedeci;
    }

    return EXIT_SUCCESS;
}

int izbrisiArtikle(PozicijaArtikla glavaArtikla)
{
    PozicijaArtikla temp = NULL;

    while (glavaArtikla->sljedeci != NULL) {
        temp = glavaArtikla->sljedeci;
        glavaArtikla->sljedeci = temp->sljedeci;
        free(temp);
    }

    return 0;
}

int izbrisiRacune(PozicijaRacuna glavaRacuna)
{
    PozicijaRacuna temp = NULL;

    while (glavaRacuna->sljedeci != NULL) {
        temp = glavaRacuna->sljedeci;
		glavaRacuna->sljedeci = temp->sljedeci;
		izbrisiArtikle(&temp->glavaArtikla);
		free(temp);
	}

	return 0;
}