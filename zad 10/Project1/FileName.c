#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)


struct _town;
typedef struct _town* TownPosition;
typedef struct _town
{
	char name[MAX_LENGTH];
	int population;
	TownPosition next;
	TownPosition left;
	TownPosition right;
} Town;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country
{
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
	TownPosition townRootTree;
	Town townListHead;
} Country;

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
CountryPosition createNewCountry(char* countryName);
TownPosition createNewTown(char* townName, int townPopulation);
int insertSortedNewTownList(TownPosition townHeadList, TownPosition newTown);
int insertTownAfter(TownPosition townCurrent, TownPosition newTown);
TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown);
int insertSortedNewCountryList(CountryPosition townHeadList, CountryPosition newCountry);
int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry);
CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry);
int printCountryList(CountryPosition countryHeadList);
int printCountryTree(CountryPosition countryRootTree);
int printTownList(TownPosition townHeadList);
int printTownTree(TownPosition townRootTree);
int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries);
CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName);

int main() {
	Country countryHeadList = {
		.name = { 0 },
		.next = NULL,
		.left = NULL,
		.right = NULL,
		.townRootTree = NULL,
		.townListHead = {
			.name = { 0 },
			.population = 0,
			.next = NULL,
			.left = NULL,
			.right = NULL,
		}
	};

	CountryPosition countryRootTree = NULL;

	CountryPosition countryCurrentList = NULL;
	CountryPosition countryCurrentTree = NULL;
	CountryPosition countries[] = { NULL, NULL };

	countryRootTree = readAndFillCountries(&countryHeadList, countryRootTree);
	printCountryList(&countryHeadList);
	printf("\n\n\n\n");
	printCountryTree(countryRootTree);

	findCountries(&countryHeadList, countryRootTree, countries);

	countryCurrentList = countries[0];
	countryCurrentTree = countries[1];

	printf("\nCountry list: %s", countryCurrentList->name);
	printf("\nCountry tree: %s", countryCurrentTree->name);


	return 0;
}

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree) {
	FILE* filePointer = NULL;
	char countryName[MAX_LINE] = { 0 };
	char countryFile[MAX_LINE] = { 0 };
	char nullString[MAX_LINE] = { 0 };
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CountryPosition countries[] = { NULL, NULL };

	filePointer = fopen("drzave.txt", "r");
	if (!filePointer) {
		printf("Can't open file!");
		return 0;
	}

	while (!feof(filePointer)) {
		fscanf(filePointer, "%s %s", countryName, countryFile);
		createNewCountryFromBuffer(countryName, countryFile, countries);
		newCountryList = countries[0];
		newCountryTree = countries[1];
		insertSortedNewCountryList(countryHeadList, newCountryList);
		countryRootTree = insertNewCountryTree(countryRootTree, newCountryTree);
		strcpy(countryName, nullString);
		strcpy(countryFile, nullString);
	}

	fclose(filePointer);

	return countryRootTree;
}

int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries) {
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryFilePointer = NULL;
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	TownPosition newTownList = NULL;
	TownPosition newTown = NULL;
	char townName[MAX_LENGTH] = { 0 };
	int townPopulation = 0;

	strcpy(countryLocation, countryFile);

	countryFilePointer = fopen(countryLocation, "r");
	if (!countryFilePointer) {
		printf("Can't open file!");
		return 0;
	}

	newCountryList = createNewCountry(countryName);
	newCountryTree = createNewCountry(countryName);

	while (!feof(countryFilePointer)) {
		fscanf(countryFilePointer, " %s %d", townName, &townPopulation);
		newTownList = createNewTown(townName, townPopulation);
		newTown = createNewTown(townName, townPopulation);
		insertSortedNewTownList(&newCountryTree->townListHead, newTownList);
		newCountryList->townRootTree = insertNewTownTree(newCountryList->townRootTree, newTown);
		newTownList = NULL;
	}
	countries[0] = newCountryList;
	countries[1] = newCountryTree;

	fclose(countryFilePointer);

	return 0;
}

CountryPosition createNewCountry(char* countryName) {
	CountryPosition country = NULL;
	country = (CountryPosition)malloc(sizeof(Country));
	if (!country) {
		printf("Can't allocate memory!\n");
		return 0;
	}


	strcpy(country->name, countryName);
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;
	country->townRootTree = NULL;
	
	country->townListHead.population = 0;
	country->townListHead.next = NULL;
	country->townListHead.left = NULL;
	country->townListHead.right = NULL;

	return country;
}

TownPosition createNewTown(char* townName, int townPopulation) {
	TownPosition town = NULL;
	town = (TownPosition)malloc(sizeof(Town));
	if (!town) {
		printf("Can't allocate memory!\n");
		return 0;
	}

	strcpy(town->name, townName);
	town->population = townPopulation;
	town->next = NULL;
	town->left = NULL;
	town->right = NULL;

	return town;
}

int insertSortedNewTownList(TownPosition townHeadList, TownPosition newTown) {
	TownPosition townCurrent = townHeadList;
	while (townCurrent->next != NULL && townCurrent->next->population > newTown->population) {
		townCurrent = townCurrent->next;
	}

	insertTownAfter(townCurrent, newTown);

	return 0;
}

int insertTownAfter(TownPosition townCurrent, TownPosition newTown) {
	newTown->next = townCurrent->next;
	townCurrent->next = newTown;

	return 0;
}

TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown) {
	if (townRootTree == NULL)
		return newTown;

	if (newTown->population > townRootTree->population)
		townRootTree->left = insertNewTownTree(townRootTree->left, newTown);
	else if (newTown->population <= townRootTree->population)
		townRootTree->right = insertNewTownTree(townRootTree->right, newTown);

	return townRootTree;
}

int insertSortedNewCountryList(CountryPosition townHeadList, CountryPosition newCountry) {
	CountryPosition countryCurrent = townHeadList;
	while (countryCurrent->next != NULL && strcmp(countryCurrent->next->name, newCountry->name) < 0) {
		countryCurrent = countryCurrent->next;
	}

	insertCountryAfter(countryCurrent, newCountry);

	return 0;
}

int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry) {
	newCountry->next = countryCurrent->next;
	countryCurrent->next = newCountry;

	return 0;
}

CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry) {
	if (countryRootTree == NULL)
		return newCountry;

	if (strcmp(countryRootTree->name, newCountry->name) > 0)
		countryRootTree->left = insertNewCountryTree(countryRootTree->left, newCountry);
	else if (strcmp(countryRootTree->name, newCountry->name) <= 0)
		countryRootTree->right = insertNewCountryTree(countryRootTree->right, newCountry);

	return countryRootTree;
}

int printCountryList(CountryPosition countryHeadList) {
	CountryPosition currentCountry = countryHeadList->next;
	while (currentCountry != NULL) {
		printf("\n%s", currentCountry->name);
		printTownTree(currentCountry->townRootTree);
		currentCountry = currentCountry->next;
	}
}

int printCountryTree(CountryPosition countryRootTree) {
	if (countryRootTree) {
		printCountryTree(countryRootTree->left);
		printf("\n%s", countryRootTree->name);
		printTownList(&countryRootTree->townListHead);
		printCountryTree(countryRootTree->right);
	}
	return 0;
}

int printTownList(TownPosition townHeadList) {
	TownPosition currentTown = townHeadList->next;
	while (currentTown != NULL) {
		printf("\n\t%s %d", currentTown->name, currentTown->population);
		currentTown = currentTown->next;
	}
}

int printTownTree(TownPosition townRootTree) {
	if (townRootTree) {
		printTownTree(townRootTree->left);
		printf("\n\t%s %d", townRootTree->name, townRootTree->population);
		printTownTree(townRootTree->right);
	}
	return 0;
}

int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries) {
	CountryPosition countryCurrentList = countryHeadList->next;
	CountryPosition countryCurrentTree = countryRootTree;
	char countryName[MAX_LENGTH] = { 0 };
	printf("\n\nEnter country name: ");
	scanf(" %s", countryName);

	while (countryCurrentList != NULL && strcmp(countryCurrentList->name, countryName)) {
		countryCurrentList = countryCurrentList->next;
	}

	countryCurrentTree = searchCountryTree(countryRootTree, countryName);

	countries[0] = countryCurrentList;
	countries[1] = countryCurrentTree;

	return 0;
}

CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName) {
	if (countryRootTree == NULL || strcmp(countryRootTree->name, countryName) == 0)
		return countryRootTree;

	if (strcmp(countryRootTree->name, countryName) > 0)
		return searchCountryTree(countryRootTree->left, countryName);

	return searchCountryTree(countryRootTree->right, countryName);
}