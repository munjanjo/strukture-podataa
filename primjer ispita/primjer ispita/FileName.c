/*napisati program koji iz datoteke student.txt cita podatke o studentima i njihovim maticnim brojevima, 
te podatke sprema u vezanu listu sortiranu po prezimenu i imenu studenta. iz datoteke pedmet1.txt procitati 
maticni broj studenta i ocjenu te ih upisati u odgovarajuci element liste. ispisati listu zatim omoguciti upis nekog 
imena sa tastature te izbrisati sve one studente koji imaju isto ime te ponovo ispisati listu.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _student student;
typedef student* pozicija;
struct _student {
	char ime[50];
	char prez[50];
	int mb;
	int ocjena;
	pozicija next;
};
pozicija readFile(pozicija);
pozicija insertIntoList(pozicija, char[], char[], int);
pozicija maloc(pozicija);
pozicija readSubject(pozicija);
pozicija insertSubject(pozicija, int, int);
pozicija izbrsiIme(pozicija, char[]);
int printList(pozicija);
int main() {
	pozicija head=NULL;
	head = readFile(head);
	head = readSubject(head);
	printList(head);
	char brisi[50];
	printf("\n\nUnesi ime koje hoces obrisati:");
	scanf("%s", brisi);
	head = izbrsiIme(head, brisi);
	printList(head);



	return 0;
}
pozicija izbrsiIme(pozicija head, char ime[]) {
	pozicija current = head;
	pozicija prev = head;
	current = current->next;
	while (current != NULL)
	{
		if (strcmp(current->ime, ime) == 0) {
			prev->next = current->next;
			free(current);
			current = prev->next;

		}
		current = current->next;
		prev = prev->next;
	}
	return head;
}
int printList(pozicija head) {
	head = head->next;
	while (head != NULL) {
		printf("%s %s %d %d\n", head->prez, head->ime, head->mb, head->ocjena);
		head = head->next;
	}
	return 0;
}
pozicija readSubject(pozicija head) {
	FILE* fp = NULL;
	int ocjena, mb;
	fp = fopen("predmet1.txt","r");
	if (fp == NULL) {
		printf("kiro otvoren file");
		return 0;
	}
	fscanf(fp, "%*s");
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &mb, &ocjena);
		head = insertSubject(head, mb, ocjena);
	}

	return head;
}
pozicija insertSubject(pozicija head, int mb, int ocjena) {
	pozicija current = head;
	if (current->next != NULL)
		current = current->next;
	while (current != NULL && (current->mb != mb)) {
		current = current->next;
	}
	current->ocjena = ocjena;


	return head;
}
pozicija readFile(pozicija head) {
	char ime[50];
	char prez[50];
	int mb;
	FILE* fp=NULL;
	fp = fopen("studenti.txt", "r");
	
	if (fp == NULL) {
		printf("krivo otovoren file");
		return 0;
	}
		
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", prez, ime, &mb);
		head = insertIntoList(head, prez, ime, mb);
	}
	fclose(fp);


	return head;
}
pozicija insertIntoList(pozicija head, char prez[], char ime[], int mb) {
	pozicija new = NULL;
	new = maloc(new);
	strcpy(new->prez, prez);
	strcpy(new->ime, ime);
	new->mb = mb;
	new->ocjena = 0;
	if (head == NULL) {
		head = maloc(head);
		return new;
	}
	pozicija current = head;
	pozicija prev = head;
	current = current->next;
	while (current != NULL&&(strcmp(current->prez, new->prez) < 0|| (strcmp(current->prez, new->prez)==0 &&strcmp(current->ime, new->ime) < 0 ))) {
		current = current->next;
		prev = prev->next;
	}
	new->next = current;
	prev->next = new;
	return head;
}
pozicija maloc(pozicija hea) {
	hea = (pozicija)malloc(sizeof(student));
	if (hea == NULL)
		return 0;
	hea->next = NULL;
	return hea;
}