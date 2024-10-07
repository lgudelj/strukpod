#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 1024
int NumberOfRows(const char*);

int main()
{

	int numofrows = 0;
	numofrows = NumberOfRows("imedat.txt");

	return 0;
}
int NumberOfRows(const char* fileName)
{
	FILE* fp = NULL;
	int numofrows = 0;
	char buffer[MAX] = {};

	fp = fopen(fileName, "r");
	if (!fp)
	{
		return -1
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		numofrows++;
	}
}