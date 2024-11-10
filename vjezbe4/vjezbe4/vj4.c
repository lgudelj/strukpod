#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element* pozicija;
typedef struct element {
    int koef;
    int exp;
    pozicija next;
}el;

void free_el(pozicija head);
pozicija kreirajelement(int koef, int exp);
void nakon(pozicija trenutni, pozicija novi);
void sortunos(pozicija head, pozicija novi);
void izbnakon(pozicija temp);
pozicija* ucitaj_dat(char* filename, pozicija** elementi, int* brojac);
void zbroji(pozicija* elementi, int brojac, pozicija rez);
void mnozi(pozicija* elementi, int brojac, pozicija rez);
void ispisel(pozicija head);

int main()
{
    pozicija* elementi = NULL;
    int br = 0;
    pozicija sum = kreirajelement(0, 0);
    pozicija umnozak = kreirajelement(0, 0);

    ucitaj_dat("pol.txt", &elementi, &br);

    zbroji(elementi, br, sum);
    mnozi(elementi, br, umnozak);

    printf("Suma elementa\n");
    ispisel(sum);

    printf("Umnozak elementa\n");
    ispisel(umnozak);

    free_el(sum);
    free_el(umnozak);

    for (int i = 0; i < br; i++)
    {
        free_el(elementi[i]);
    }
    free(elementi);

    return 0;
}

void free_el(pozicija head)
{
    while (head != NULL)
    {
        pozicija temp = head;
        head = head->next;
        free(temp);
    }
}

pozicija kreirajelement(int koef, int exp)
{
    pozicija novi = NULL;
    novi = (pozicija)malloc(sizeof(el));
    if (novi == NULL)
    {
        printf("neuspjesna alokacija memorije\n");
        return NULL;
    }

    novi->koef = koef;
    novi->exp = exp;
    novi->next = NULL;

    return novi;
}

void nakon(pozicija trenutni, pozicija novi) 
{
    if (trenutni != NULL && novi != NULL) 
    {
        novi->next = trenutni->next;
        trenutni->next = novi;
    }
}

void sortunos(pozicija head, pozicija novi) 
{
    pozicija temp = head;

    while (temp->next && (temp->next->exp < novi->exp)) 
    { 
        temp = temp->next;
    }

    if (temp->next == NULL || temp->next->exp != novi->exp) 
    {
        nakon(temp, novi);
    }
    else 
    {
        int rezkoef = temp->next->koef + novi->koef;
        if (rezkoef == 0) 
        {
            izbnakon(temp);
            free(novi);
        }
        else 
        {
            temp->next->koef = rezkoef;
            free(novi);
        }
    }
}

void izbnakon(pozicija temp) 
{
    if (temp == NULL || temp->next == NULL) 
    {
        return;
    }
    pozicija todelete = temp->next;
    temp->next = todelete->next;
    free(todelete);
}

pozicija* ucitaj_dat(char* filename, pozicija** elementi, int* brojac) 
{
    FILE* file = NULL;
    file = fopen(filename, "r");
    if (!file) 
    {
        printf("nemoguce otvoriti datoteku\n");
        return NULL;
    }

    char buffer[1024];
    int c, e, numBytes;
    *brojac = 0;

    *elementi = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        pozicija head = kreirajelement(0, 0);   
        char* line = buffer;

        while (strlen(line) > 0) 
        {
            
            int status = sscanf(line, " %d %d %n", &c, &e, &numBytes); 
            if (status == 2) 
            {
                pozicija q = kreirajelement(c, e);
                sortunos(head, q);
            }
            else 
            {
                printf("datoteka nije valjana\n");
                fclose(file);
                return NULL;
            }

            line += numBytes;
        }

        (*brojac)++;
        pozicija* temp = realloc(*elementi, (*brojac) * sizeof(pozicija));
        if (!temp) 
        {
            printf("neuspjesna alokacija memorije\n");
            fclose(file);
            return NULL;
        }
        *elementi = temp;
        (*elementi)[(*brojac) - 1] = head;   
    }

    fclose(file);
    return *elementi;
}

void zbroji(pozicija* elementi, int brojac, pozicija rez) 
{
    for (int i = 0; i < brojac; i++) 
    {
        pozicija p = elementi[i]->next;
        while (p != NULL) 
        {
            sortunos(rez, kreirajelement(p->koef, p->exp));
            p = p->next;
        }
    }
}

void mnozi(pozicija* elementi, int brojac, pozicija rez) 
{
    if (brojac == 0) return;

    
    pozicija temp_rez = kreirajelement(0, 0);
    sortunos(temp_rez, kreirajelement(1, 0));

    for (int i = 0; i < brojac; i++) 
    {
        
        pozicija inter = kreirajelement(0, 0);
        pozicija p1 = temp_rez->next;

        
        while (p1 != NULL) 
        {
            pozicija p2 = elementi[i]->next;
            while (p2 != NULL) 
            {
                int novi_koef = p1->koef * p2->koef;
                int novi_exp = p1->exp + p2->exp;
                sortunos(inter, kreirajelement(novi_koef, novi_exp));
                p2 = p2->next;
            }
            p1 = p1->next;
        }

        
        while (temp_rez->next != NULL) 
        {
            izbnakon(temp_rez);
        }

        
        temp_rez->next = inter->next;
        free(inter);
    }

    rez->next = temp_rez->next;
    free(temp_rez);
}

void ispisel(pozicija head) 
{
    pozicija temp = head->next;
    while (temp) 
    {
        printf("%dx^%d ", temp->koef, temp->exp);
        if (temp->next) 
        {
            printf("+ ");
        }
        temp = temp->next;
    }
    printf("\n");
}