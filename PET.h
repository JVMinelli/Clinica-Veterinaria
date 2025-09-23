#ifndef PET_H_INCLUDED
#define PET_H_INCLUDED
#include "FILA.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


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
    int atendido;
}Pet;

void imprimePetAtendido(Pet* p, int max_nome, int max_especie);
void imprimePet(Pet* p);
void imprimeFila(Fila *fila);
void imprimeFilaAtendidos(Fila *fila);
int maiorNome(Fila *fila);
int maiorEspecie(Fila *fila);
Pet* criaPet(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
int idIsValid(int new_id, Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
int generateId(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
Fila* buscarPetNome(char *nome, Fila *fila_emergencia, Fila *fila_normal, Fila *fila_atendidos);
Pet* buscarPetId(int id, Fila *fila_emergencia, Fila *fila_normal, Fila *fila_atendidos);



Pet* criaPet(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos) {
    Pet* new_pet = (Pet*)malloc(sizeof(Pet));
    if (new_pet == NULL) {
        printf("Erro: Falha na alocação de memória para o Pet.\n");
        return NULL;
    }

    new_pet->data = (Data*)malloc(sizeof(Data));
    if (new_pet->data == NULL) {
        printf("Erro: Falha na alocação de memória para a data.\n");
        free(new_pet);
        return NULL;
    }
    while (getchar() != '\n');
    printf("\nDigite o nome do pet: ");
    fflush(stdin);
    fgets(new_pet->nome,sizeof(new_pet->nome),stdin);
    new_pet->nome[strcspn(new_pet->nome, "\n")] = '\0';
    fflush(stdin);

    int itens_lidos;

    do {
        printf("\nDigite a idade do pet: ");
        itens_lidos = scanf("%d", &new_pet->idade);
        fflush(stdin);

        if (itens_lidos != 1) {
            printf("Entrada inválida. Por favor, digite um número para a idade.\n");
        }
    } while (itens_lidos != 1);
    while (getchar() != '\n');
    printf("\nDigite a espécie do pet: ");
    fgets(new_pet->especie,sizeof(new_pet->especie),stdin);
    new_pet->especie[strcspn(new_pet->especie, "\n")] = '\0';
    fflush(stdin);
    do {
        printf("\nDigite a data de nascimento do pet (DD/MM/AAAA). Ex: 02/09/2005: ");
        itens_lidos = scanf("%d/%d/%d", &new_pet->data->dia, &new_pet->data->mes, &new_pet->data->ano);
        while (getchar() != '\n');

        if (itens_lidos != 3) {
            printf("Formato de data inválido. Tente novamente.\n");
        }
    } while (itens_lidos != 3);

    char prioridade;
    do {
        printf("\nEmergência? (S/N): ");
        itens_lidos = scanf(" %c", &prioridade);
        fflush(stdin);

        prioridade = toupper(prioridade);

        if (itens_lidos != 1 || (prioridade != 'S' && prioridade != 'N')) {
            printf("Opção inválida. Por favor, digite 'S' para sim ou 'N' para não.\n");
        }
    } while (itens_lidos != 1 || (prioridade != 'S' && prioridade != 'N'));

    new_pet->prioridade = (prioridade == 'S') ? 1 : 0;

    new_pet->atendido = 0;

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
    Pet *pet = buscarPetId(new_id,fila_emergencia, fila_normal,fila_atendidos);
    if(pet == NULL){
        return 1;
    }
    return 0;
}

void imprimePetAtendido(Pet* p, int max_nome, int max_especie)
{
    char nome[max_nome];
    memset(nome,' ',max_nome);
    nome[max_nome] = '\0';
    int tam = (strlen(p->nome));
    for(int i=0; i<tam;i++){
        nome[i] = p->nome[i];
    }
    char especie[max_especie];
    memset(especie,' ',max_especie);
    especie[max_especie] = '\0';
    tam = (strlen(p->especie));
    for(int i=0; i<tam;i++){
        especie[i] = p->especie[i];
    }

    char idade_padding[6];
    char str_number[20];
    fflush(stdin);
    sprintf(str_number, "%d", p->idade);
    memset(idade_padding,' ',6);
    idade_padding[5] = '\0';
    for(int i=0; i<2;i++){
        idade_padding[i] = str_number[i];
    }
    printf("\n\t%d | %s ",p->id,nome);
    printf("| %s | %s | %s | %s ",especie,idade_padding,(p->prioridade) ? ("EMERGENCIA") : ("  NORMAL  "), (p->atendido) ? ("ATENDIDO") : ("AGUARDANDO ATENDIMENTO"));
}

void imprimePet(Pet* p)
{
    printf("\n\t%d | %s | %s | %02d | %02d/%02d/%04d | %s\n",p->id,p->nome,p->especie,p->idade,p->data->dia,p->data->mes,p->data->ano,(p->prioridade) ? ("EMERGENCIA") : ("NORMAL"));
}

void imprimeFila(Fila *fila){
    Nos *aux;
    if(!VaziaFila(fila)){
        aux = fila->ini;
        while(aux != NULL){
            imprimePet(aux->pet);
            aux = aux->prox;
        }
    }
}

void imprimeFilaAtendidos(Fila *fila){
    Nos *aux;
    int max_especies = maiorEspecie(fila);
    int max_nome = maiorNome(fila);
    char nome_t[max_nome];
    char nome[5] = "Nome";
    memset(nome_t,' ',max_nome);
    nome_t[max_nome] = '\0';
    int tam = (strlen(nome));
    for(int i=0; i<tam;i++){
        nome_t[i] = nome[i];
    }

    char especie_t[max_nome];
    char especie[8] = "Especie";
    memset(especie_t,' ',max_nome);
    especie_t[max_nome] = '\0';
    tam = (strlen(especie));
    for(int i=0; i<tam;i++){
        especie_t[i] = especie[i];
    }
    printf("\n\tID  | %s | %s| Idade | Prioridade | Atendido \n",nome_t,especie_t);

    if(!VaziaFila(fila)){
        aux = fila->ini;
        while(aux != NULL){
            imprimePetAtendido(aux->pet,max_nome,max_especies);
            aux = aux->prox;
        }
    }
}

int maiorNome(Fila *fila){
    Nos* aux = fila->ini;
    int max = strlen(aux->pet->nome);
    while(aux!=NULL){
        int temp = strlen(aux->pet->nome);
        if(temp > max){
            max = temp;
        }
        aux = aux->prox;
    }
    return max;
}

int maiorEspecie(Fila *fila){
    Nos* aux = fila->ini;
    int max = strlen(aux->pet->especie);
    while(aux!=NULL){
        int temp = strlen(aux->pet->especie);
        if(temp > max){
            max = temp;
        }
        aux = aux->prox;
    }
    return max;
}

Fila* buscarPetNome(char *nome, Fila *fila_emergencia, Fila *fila_normal, Fila *fila_atendidos){

    Nos *aux;
    Fila *fila_nomes = CriaFila();

    aux = fila_normal->ini;
    while(aux != NULL){
        if(strncmp(aux->pet->nome,nome,sizeof(aux->pet->nome))==0){
            InsereFila(fila_nomes, aux->pet);
        }
        aux = aux->prox;
    }

    aux = fila_emergencia->ini;
    while(aux != NULL){
        if(strncmp(aux->pet->nome,nome,sizeof(aux->pet->nome))==0){
            InsereFila(fila_nomes, aux->pet);
        }
        aux = aux->prox;
    }

    aux = fila_atendidos->ini;
    while(aux != NULL){
        if(strncmp(aux->pet->nome,nome,sizeof(aux->pet->nome))==0){
            InsereFila(fila_nomes, aux->pet);
        }
        aux = aux->prox;
    }

    return fila_nomes;
}

Pet* buscarPetId(int id, Fila *fila_emergencia, Fila *fila_normal, Fila *fila_atendidos){

    Nos *aux;

    aux = fila_normal->ini;
    while(aux != NULL){
        if(aux->pet->id == id){
            return aux->pet;
        }
        aux = aux->prox;
    }

    aux = fila_emergencia->ini;
    while(aux != NULL){
        if(aux->pet->id == id){
            return aux->pet;
        }
        aux = aux->prox;
    }

    aux = fila_atendidos->ini;
    while(aux != NULL){
        if(aux->pet->id == id){
            return aux->pet;
        }
        aux = aux->prox;
    }

    return NULL;
}

#endif
