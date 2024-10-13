
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 1024
#define MAX_POINTS 100

typedef struct 
{
    char ime[MAX];
    char prez[MAX];
    int bod;
} student;

int NumberOfRows(const char* fileName);

int main() {
    int numofrows = 0;
    numofrows = NumberOfRows("students.txt");

    if (numofrows == -1) {
        printf("greska\n");
        return 0;
    }

    student* s = (student*)malloc(numofrows * sizeof(student));
    if (s == NULL) {
        printf("greska \n");
        return 0;
    }

    FILE* fp = fopen("students.txt", "r");
    if (!fp) 
    {
        printf("greska \n");

        return 0;
    }

    for (int i = 0; i < numofrows; i++) 
    {
        fscanf(fp, "%s %s %d", s[i].ime, s[i].prez, &s[i].bod);
    }

    for (int i = 0; i < numofrows; i++) 
    {
        printf("%s %s %d %f\n", s[i].ime, s[i].prez, s[i].bod, s[i].bod / (float)MAX_POINTS * 100);
    }

    

    return 0;
}
int NumberOfRows(const char* fileName)
{
    FILE* fp = NULL;
    int numofrows = 0;
    char buffer[MAX] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) 
    {
        return -1;
    }

    while (fgets(buffer, MAX, fp) != NULL) 
    {
        numofrows++;
    }



    return numofrows;
}