# strukpod
repository for data structures
123
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define MAX 1024

struct  _person;//postoji ta struk
typedef struct _person* position;
typedef struct _person
{
	char name [MAX];
	char surname [MAX];
	char birthYear;
	position next;



}Person;//sad u mainu zovemo Person

position CreatePerson(char* name, char* surname, int birthyear);

int PrependList(position head, char* name, char* surname, int birthYear);
int PrintList(position first);

int main()
{
	Person head =
	{
		.name = {0},
		.surname = {0},
		.birthYear = {0},
		.next=NULL
	};




	return 0;
}

position CreatePerson(char* name, char* surname, int birthYear)
{
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("bad allocation! \n");
		return NULL;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;
	return newPerson;
}


int PrependList(position head, char* name, char* surname, int birthYear)
{
	newPerson->next = head->next;
	newPers
	return EXIT_SUCCESS;
}

int PrintList(position first)
{
	position temp = NULL;

	temp = first;
	while (temp != NULL)
	{
		printf("%s  %s %d", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int AppendList(position head, char* name, char)


position FindLast(position Head)
{
	position last = NULL;
	last = head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return last;
}
int insertafter( position prev position newperson)
newperson->next = prev->next;
prev->next = newperson;
return EXIT_SUCCESS;

position nadi po prezimenu(position first, char* surname)
{
	psoition temp = NULL
		Temp = first;
	while (temp)
	{
		if (strcmp(surname, temp->surname) == 0)
		{
			return temp;
		}
		temp = temp->next;

	}
	return NULL;
}
INT delete(position head, char* name)
{

}
