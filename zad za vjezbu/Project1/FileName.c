#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)
struct _CountryList;
typedef struct _CountryList* CountryListPosition;
struct _CityTree;
typedef struct _CityTree* CityTreePosition;

typedef struct _CountryList {
	char countryname[MAX_LENGTH];
	CountryListPosition next;
	CityTreePosition root;
}CountryList;
typedef struct _CityTree {
	char cityname[MAX_LENGTH];
	int population;
	CityTreePosition left;
	CityTreePosition right;

}CityTree;



int readFile(CountryListPosition);
CountryListPosition insertIntoList(CountryListPosition, char*, char*);
CountryListPosition createNewCountry(CountryListPosition);
int readCity(char[], CityTreePosition);
CityTreePosition createNewCity(char[], int);
CityTreePosition insertIntoTree(CityTreePosition, CityTreePosition);
int printAll(CountryListPosition);
int inOrderPrint(CityTreePosition);

int main() {
	CountryList _listHead = { .countryname = "0", .root = NULL, .next = NULL };
	CountryListPosition listHead = &_listHead;
	readFile(listHead);
	printAll(listHead);
	return 0;
}
int readFile(CountryListPosition listHead ) {
	FILE* fp = NULL;
	char countryName[MAX_LENGTH];
	char countryFile[MAX_LENGTH];
	fp = fopen("drzave.txt", "r");
	if (!fp) {
		printf("krivo otvorene drzave\n");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s", countryName, countryFile);
		listHead = insertIntoList(listHead, countryName, countryFile);
	}
	fclose(fp);
	return 0;

}
CountryListPosition insertIntoList(CountryListPosition listHead, char* name, char* file) {
	CountryListPosition new = NULL;
	new = createNewCountry(new);
	char countryFile[MAX_LENGTH] = { 0 };
	strcpy(new->countryname, name);
	new->next = listHead->next;
	listHead->next = new;
	strcpy(countryFile, file);
	readCity(countryFile,new->root);

	return listHead;
}
CountryListPosition createNewCountry(CountryListPosition new)
{
	new = (CountryListPosition)malloc(sizeof(CountryList));
	if (new == NULL)
	{
		printf("krivo allociranje\n");
		return 0;
	}
	new->next = NULL;
	new->root = NULL;
	return new;
}
int readCity(char file[],CityTreePosition root) {
	char cityName[MAX_LENGTH];
	int population;
	CityTreePosition new;
	FILE* fp = NULL;
	fp = fopen(file, "r");
	if (!fp) {
		printf("krivo otvoreni gradovi\n");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %d", cityName, &population);
		new = createNewCity(cityName, population);
		root = insertIntoTree(root, new);

	}
	fclose(fp);
	

	

	return 0;
}
CityTreePosition createNewCity(char cityname[], int population) {
	CityTreePosition new = NULL;
	new = (CityTreePosition)malloc(sizeof(CityTree));
	if (!new) {
		printf("krivo allociran prostor za grad");
		return 0;
	}
	strcpy(new->cityname, cityname);
	new->population = population;
	new->right = NULL;
	new->left = NULL;
	return new;

}
CityTreePosition insertIntoTree(CityTreePosition root, CityTreePosition new) {
	if (root==NULL) {
		printf("nema root vracen new\n");
		return new;
	}
		
		
	else if (new->population < root->population)
		root->left = insertIntoTree(root->left, new);
	else if (new->population >= root->population)
		root->right = insertIntoTree(root->right, new);
	return root;
}
int printAll(CountryListPosition listHead) {
	listHead = listHead->next;
	while (listHead) {
		printf("%s\n", listHead->countryname);
		inOrderPrint(listHead->root);
		listHead = listHead->next;
	}



	return 0;
}
int inOrderPrint(CityTreePosition root) {
	if (!root) {
		printf("nema root\n");
		return 0;
		
	}
	inOrderPrint(root->left);
	printf("   %s  %d\n", root->cityname, root->population);
	inOrderPrint(root->right);
	return 0;
}