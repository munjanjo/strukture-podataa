#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct racun* pozicija;
struct racun {
	float br;
	pozicija next;
};
typedef struct racun racun;
pozicija createHead();
int citanjeDatoteke(char[MAX], pozicija);
void dodajNaStog(int, pozicija);
void uzmiSaStoga(char, pozicija);
void brisiElement(pozicija);
void ispisRezultata(pozicija);
void brisiSve(pozicija);
int main() {
	int status = 0;
	pozicija head = NULL;
	head = createHead();
	char imeDatoteke[MAX];
	printf("unesi ime datoteke:");
	scanf("%s%*c", imeDatoteke);
	citanjeDatoteke(imeDatoteke, head);
	ispisRezultata(head);
	brisiSve(head);


	return 0;
}
pozicija createHead() {
	pozicija p=NULL;
	p = (pozicija)malloc(sizeof(racun));
	if (p == NULL) {
		printf("krivo alocirano\n");
		return -1;
	}
	p->next=NULL;
	return p;
}
int citanjeDatoteke(char ime[MAX], pozicija p) {
	int status = 0, n = 0;
	int tmp = 0, br = 0;
	char buffer[1024] = { 0 };
	char* buf;
	char operacija = '\0';
	FILE* fp = NULL;
	fp = fopen(ime, "r");
	if (fp == NULL) {
		printf("krivo otvaranje datoteke!!");
		return -1;
	}
	fgets(buffer, 1024, fp);
	buf = buffer;
	printf("\nPostfix izraz iscitan iz datoteke:\n%s", buffer);
	while (strlen(buf) != 0) {
		status = sscanf(buf,"%d %n", &br, &n);
		if (status == 1) {
			dodajNaStog(br, p);
		}
		else {
			sscanf(buf, "%c %n", &operacija, &n);
			uzmiSaStoga(operacija, p);
		}

		buf = buf + n;
	}
	fclose(ime);

	return 0;
}
void dodajNaStog(int br, pozicija p) {
	pozicija q = NULL;
	q = createHead();
	if (q == NULL)
	{
		printf("\npogresno alociranje memorije stog!!");
		return -1;

	}
	q->next = p->next;
	p->next = q;
	q->br = (float)br;
	return 0;



}
void uzmiSaStoga(char operacija, pozicija p) {
	float rezultat = 0;
	pozicija head = NULL;
	head = p;
	pozicija pret = NULL;
	p =p->next;
	pret = p->next;
	switch (operacija)
	{
	case '+':
	{
		rezultat = (pret->br) + (p->br);
		break;
	}
	case '*':
	{
		rezultat = (pret->br) * (p->br);
		break;
	}
	case '/':
	{
		if (p->br == 0) {
			printf("\nDijeljenje s nulom nije dozvoljeno!");
			return -1;
		}
		else {
			rezultat = (pret->br) / (p->br);
			break;
		}
	}
	case '-':
	{
		rezultat = (pret->br) - (p->br);
		break;
	}
	}
	pret->br = rezultat;
	brisiElement(head);
	return 0;
}
void brisiElement(pozicija p) {
	pozicija temp;
	temp = p->next;
	p->next = temp->next;
	free(temp);

}
void ispisRezultata(pozicija p) {
	printf("\nRezultat je:%.2lf", p->next->br);
	return 0;
}
void brisiSve(pozicija p) {
	pozicija temp=NULL;
	while (p != NULL)
	{
		temp = p;
		p = p->next;
		free(temp);
	}
	return 0;

}
