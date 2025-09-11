#ifndef PET_H_INCLUDED
#define PET_H_INCLUDED
#include "FILA.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>


typedef struct DataNasci
{
    int dia;
    int mes;
    int ano;
}Data;
typedef struct petInfo
{
    int id;
    int idade;
    char especie[30];
    char nome[50];
    Data *data;
    int prioridade;
}Pet;

/**
* Funções de Impressão de Pet
*/
void imprimePetAtendido(Pet* p);
void imprimePet(Pet* p);
/**
* Funções para criar um Pet
*/
Pet* criaPet(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
int idIsValid(int new_id, Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
int generateId(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);

void imprimePetAtendido(Pet* p)
{
    printf("\n\t%d | %s | %s | %d | %s",p->id,p->nome,p->especie,p->idade,(p->prioridade) ? ("EMERGENCIA") : ("NORMAL"));
}
void imprimePet(Pet* p)
{
    printf("\n\t%d | %s | %s | %d | %02d/%02d/%04d | %s",p->id,p->nome,p->especie,p->idade,p->data->dia,p->data->mes,p->data->ano,(p->prioridade) ? ("EMERGENCIA") : ("NORMAL"));
}
Pet* criaPet(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos){
    Pet* new_pet = (Pet*)malloc(sizeof(Pet));
    if (new_pet == NULL) return NULL;
    char buffer[5];

    printf("\nDigite o nome do pet: ");
    scanf("%49s", new_pet->nome);
    printf("\nDigite a idade do pet: ");
    scanf("%d", &new_pet->idade);
    printf("\nDigite a espécie do pet: ");
    scanf("%29s", new_pet->especie);
    int itens_lidos;
    do{
        printf("\nDigite a data de nacimento do pet (D/M/A). \n EX: 02/09/2005 : ");
        itens_lidos = scanf("%d/%d/%d", &new_pet->data->dia, &new_pet->data->mes, &new_pet->data->ano);
        if(itens_lidos!= 3){
            printf("Formato inválido");
            while (getchar() != '\n');
        }
    }while(itens_lidos != 3);
    char prioridade;
    printf("\nEmergencia? (Y/n): ");
    scanf("%c",&prioridade);
    while(getchar() != '\n');
    new_pet->prioridade = (toupper(prioridade) == 'Y') ? 1 : 0;
    new_pet->id = generateId(fila_normal, fila_emergencia, fila_atendidos);
    return new_pet;
}

int generateId(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos){
    int id;
    do{
        id = 100 + rand() % 900;
    } while(!idIsValid(id, fila_normal, fila_emergencia, fila_atendidos));
    return id;
}

int idIsValid(int new_id, Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos){
    Nos *aux;

    aux = fila_normal->ini;
    while(aux != NULL){
        if(aux->pet->id == new_id){
            return 0;
        }
        aux = aux->prox;
    }

    aux = fila_emergencia->ini;
    while(aux != NULL){
        if(aux->pet->id == new_id){
            return 0;
        }
        aux = aux->prox;
    }

    aux = fila_atendidos->ini;
    while(aux != NULL){
        if(aux->pet->id == new_id){
            return 0;
        }
        aux = aux->prox;
    }

    return 1;
}

#endif // PET_H_INCLUDED
