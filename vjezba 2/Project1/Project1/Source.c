#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
typedef struct _osoba osoba;
typedef osoba* pozicija;
struct _osoba {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int year;
	osoba* next;
};

osoba* AddAtBeggining(pozicija people);
void PrintList(osoba* people);
pozicija AddAtEnd(osoba* pozicija);
void SearchBySurname(osoba* people);
void Delete(osoba* people);
osoba* AddAfterSomeone(osoba* people);
osoba* AddBeforeSomeone(osoba* people);
void upisUdatoteku(pozicija);

int main() {
	pozicija head = NULL;
	head = (pozicija)malloc(sizeof(osoba));
	head->next = NULL;
	char znak = NULL;
	printf("Unesi A za(dodati novi element na pocetak liste)\n"
		"Unesi B za(ispis liste)\n"
		"Unesi C za(dinamicki dodati novi element na kraj liste)\n"
		"Unesi D za(trazenje element u listi (po prezimenu))\n"
		"Unesi E za(brisanje odredenog elementa iz liste)\n"
		"Unesi G za(dodavanje nakon nekog elementa)\n"
		"Unesi H za(dodavanje prije nekog odredenog)\n"
		"Unesi J za(ispisivanje liste u file)\n"
		"Unesi F za kraj\n");

	scanf("%c", &znak);

	while (znak != 'F' && znak != 'f') {
		switch (znak) {
		case 'A':
		case 'a':
			head->next=AddAtBeggining(head->next);
			break;
		case 'B':
		case 'b':
			PrintList(head->next);
			break;
		case 'C':
		case 'c':
			head->next=AddAtEnd(head->next);
			break;
		case 'D':
		case 'd':
			SearchBySurname(head->next);
			break;
		case 'E':
		case 'e':
			Delete(head);
			break;
		case 'G':
		case 'g':
			head->next = AddAfterSomeone(head->next);
			break;
		case 'H':
		case 'h':
			head= AddBeforeSomeone(head);
			break;
		case'J':
		case 'j':
			upisUdatoteku(head->next);



		default:
			break;

		}
		printf("Unesi A za(dodati novi element na pocetak liste)\n"
			"Unesi B za(ispis liste)\n"
			"Unesi C za(dinamicki dodati novi element na kraj liste)\n"
			"Unesi D za(trazenje element u listi (po prezimenu))\n"
			"Unesi E za(brisanje odredenog elementa iz liste)\n"
			"Unesi G za(dodavanje nakon odredenog elementa)\n"
			"Unesi H za(dodavanje nekog elementa prije odredenog)\n"
			"Unesi J za(ispisivanje liste u file)\n"
			"Unesi F za kraj\n");

		scanf(" %c", &znak);
	}

	return 0;
}
osoba* AddAtBeggining(pozicija head) {
	pozicija new = (osoba*)malloc(sizeof(osoba));
	printf("Unesite Ime osobe\n");
	scanf("%s", new->name);
	printf("Unesite Prezime osobe\n");
	scanf("%s", new->surname);
	printf("Unesite Godiste osobe\n");
	scanf("%d", &new->year);
	new->next = NULL;
	if (head == NULL) {
		return new;
	}
	else {

		new->next = head;
		return new;
	}

}
void PrintList(osoba* people) {
	printf("\n\n");
	int indeks = 0;
	while (people != NULL) {
		printf("%d.%s %s %d\n", indeks, people->name, people->surname, people->year);
		people = people->next;
		indeks++;
	}
	printf("\n\n");
}
pozicija AddAtEnd(pozicija people) {
	pozicija new = (osoba*)malloc(sizeof(osoba));
	pozicija current = (osoba*)malloc(sizeof(osoba));
	current = people;
	printf("Unesite Ime osobe\n");
	scanf("%s", new->name);
	printf("Unesite Prezime osobe\n");
	scanf("%s", new->surname);
	printf("Unesite Godiste osobe\n");
	scanf("%d", &new->year);
	new->next = NULL;
	if (people == NULL) {
		return new;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = new;
	return people;
}
void SearchBySurname(osoba* people) {
	char name[MAX_SIZE];
	printf("\nupisi prezime koje zeelite naci:");
	scanf("%s", name);
	while (people != NULL) {
		if (!strcmp(name, people->surname)) {
			printf("%s %s %d\n", people->name, people->surname, people->year);
		}
		people = people->next;
	}
}
void Delete(osoba* previous)
{
	pozicija current;
	current = previous->next;
	char name[MAX_SIZE];
	printf("\nupisi prezime koje zeelite naci:");
	scanf("%s", name);
	while (current != NULL) {
		if (!strcmp(name, current->surname)) {
			previous->next = current->next;
			free(current);
			return;
		}
		current = current->next;
		previous = previous->next;
		
	}
}
osoba* AddAfterSomeone(osoba* people) {
	osoba* new = (osoba*)malloc(sizeof(osoba));
	osoba* all = people;
	printf("unesi prezime iza kojega zelis unijeti novi clan:");
	char temp[MAX_SIZE] = { 0 };
	scanf("%s", temp);
	
	printf("\nUnesite Ime osobe");
	scanf("%s", new->name);
	printf("Unesite Prezime osobe\n");
	scanf("%s", new->surname);
	printf("Unesite Godiste osobe\n");
	scanf("%d", &new->year);
	while (people != NULL) {
		if (strcmp(people->surname, temp) == 0) {

			new->next = people->next;
			people->next = new;
			return all;
		}
		people = people->next;

	}
	printf("\nne potoji to prezime");
	return all;
}
osoba* AddBeforeSomeone(osoba* current) {
	pozicija all=current;
	pozicija previous=current;
	current = current->next;
	pozicija new = (pozicija)malloc(sizeof(osoba));
	printf("unesi prezime ispred kojega zelis unijeti novi clan:");
	char temp[MAX_SIZE] = { 0 };
	scanf("%s", temp);
	
	printf("\nUnesite Ime osobe");
	scanf("%s", new->name);
	printf("Unesite Prezime osobe\n");
	scanf("%s", new->surname);
	printf("Unesite Godiste osobe\n");
	scanf("%d", &new->year);
	while (current != NULL) {
		if (strcmp(current->surname, temp) == 0) {
			new->next = current;
			previous->next = new;
			return all;
		}
		current = current->next;
		previous = previous->next;
	}
	printf("\nnije pronadeno to prezime");
	return all;
}
void upisUdatoteku(pozicija people) {
	FILE* fp;
	fp = fopen("osoba", "w");
	while (people != NULL)
	{
		fprintf(fp, "ime:%s prezime:%s godina rodenja:%d\n", people->name, people->surname, people->year);
		people = people->next;
	}
	fclose(fp);

}
