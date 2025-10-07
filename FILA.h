#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct petInfo Pet;

typedef struct nos
{
    Pet *pet;
    struct nos *prox;
} Nos;

typedef struct fila
{
    Nos *ini;
    Nos *fim;
} Fila;

Fila* CriaFila();
int VaziaFila(Fila* f);
void InsereFila(Fila* f, Pet *v);
Pet* RetiraFila(Fila* f);
Fila* liberaFila(Fila* f);

int VaziaFila(Fila* f)
{
    return (f->ini == NULL);
}

Fila* CriaFila()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* ins_fim(Nos *fim, Pet *pet_info)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->pet = pet_info;
    p->prox = NULL;
    if (fim != NULL)
        fim->prox = p;
    return p;
}

void InsereFila(Fila* f, Pet *pet_info)
{
    f->fim = ins_fim(f->fim, pet_info);
    if (f->ini == NULL)
        f->ini = f->fim;
}

Nos* retira_ini(Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

Pet* RetiraFila(Fila* f)
{
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        return NULL;
    }

    Pet* p = f->ini->pet;

    f->ini = retira_ini(f->ini);
    if (f->ini == NULL)
        f->fim = NULL;
    return p;
}

Fila* liberaFila(Fila* f)
{
    Nos* p = f->ini;
    while (p != NULL)
    {
        Nos* t = p->prox;
        free(p->pet->data);
        free(p->pet);
        free(p);
        p = t;
    }
    free(f);
    return NULL;
}
#endif
