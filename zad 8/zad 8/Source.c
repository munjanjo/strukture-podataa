
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct stablo* pozicija;

struct stablo
{
    int broj;
    pozicija desno;
    pozicija lijevo;
};

typedef struct stablo stablo;

pozicija createStruct(pozicija);
pozicija unosElementa(pozicija, pozicija);
int inorder(pozicija);
int preorder(pozicija);
int postorder(pozicija);


int main()
{
    pozicija q = NULL;
    int operacija = 0;
    int brEl = 0;
    pozicija root = NULL;
    root = createStruct(root);
    printf("unesi root element: ");
    scanf("%d", &root->broj);
    while (1)
    {
        printf("\n---------MENI--------");
        printf("\n1) Unos novog elementa");
        printf("\n2) Ispis stabla (inorder)");
        printf("\n3) Ispis stabla (preorder)");
        printf("\n4) Ispis stabla (postorder)");
        printf("\n5) exit!");
        printf("\nOdaberite operaciju: ");
        scanf("%d", &operacija);
        switch (operacija)
        {
        case 1:
            q = createStruct(q);
            if (q == NULL)
                return -1;

            printf("\nunesi noi elemnt: ");
            scanf("%d", &q->broj);
            root = unosElementa(root, q);
            break;
        case 2:
            inorder(root);
            break;
        case 3:
            preorder(root);
            break;
        case 4:
            postorder(root);
            break;
        case 5:
            return 0;


        }
        

    }

    return 0;
}
pozicija createStruct(pozicija p) {
    p = (pozicija)malloc(sizeof(stablo));
    if (p == NULL) {
        printf("Kiro allociranje memorije ");
        return -1;

    }
    p->lijevo = NULL;
    p->desno = NULL;
    return p;

}
pozicija unosElementa(pozicija p, pozicija q) {
    if (p == NULL)
        return q;
    if (p->broj < q->broj) {
        p->desno = unosElementa(p->desno, q);
    }
    else if (p->broj > q->broj) {
        p->lijevo = unosElementa(p->lijevo, q);
    }
    else {
        printf("element ec postoji");
        free(q);
    }
    return p;
       
}
int inorder(pozicija p) {
    if (p != NULL) {
        inorder(p->lijevo);
        printf("%d ", p->broj);
        inorder(p->desno);

    }
    return 0;
}
int preorder(pozicija p) {
    if (p != NULL) { 
        printf("%d ", p->broj);
        inorder(p->lijevo);
       
        inorder(p->desno);

    }
    return 0;
}
int postorder(pozicija p) {
    if (p != NULL) {
        inorder(p->lijevo);

        inorder(p->desno);
        printf("%d ", p->broj);
    }
    return 0;
}


