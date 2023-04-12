
#include <stdlib.h>
#include "bidefun.h"


PNoBookSE criaNoBookSE(void)
{
    PNoBookSE p = (PNoBookSE) malloc(sizeof(NoBookSE));
    p->prox = NULL;
    return p;
}

void destroiNoBookSE(PNoBookSE p)
{
    free(p);
}

PNoBookSE insereRegistroSE(TBook book, PNoBookSE head)
{
    PNoBookSE p;   

    if(head == NULL)
    {
        head = criaNoBookSE();
        p = head;
    }else{
        p = head;
        while(p->prox != NULL)
            p = p->prox;
        p->prox = criaNoBookSE();
        p = p->prox;
    }
    
    p->bookID = book.bookID;
    // ...

    return head;
}