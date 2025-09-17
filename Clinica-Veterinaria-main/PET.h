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

/**
* Funções de Impressão de um Pet
*/
/*
Imprime os dados de um pet já atendido
ID | Nome | Espécie | Idade | Prioridade | Atendido |
*/
void imprimePetAtendido(Pet* p, int max_nome, int max_especie);

/*
Imprime os dados de um pet não atentido
ID | Nome | Espécie | Idade | Data de Nascimento | Prioridade
*/
void imprimePet(Pet* p);

/**
* Funções de impreção das Filas
*/
void imprimeFila(Fila *fila);
void imprimeFilaAtendidos(Fila *fila);
//auxiliar
int maiorNome(Fila *fila);
int maiorEspecie(Fila *fila);


/**
* Função para criar um Pet
*/
Pet* criaPet(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
//Auxiliares
int idIsValid(int new_id, Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);
int generateId(Fila *fila_normal, Fila *fila_emergencia, Fila *fila_atendidos);

/**
* Funções de busca
*/
/*  @brief: Busca por Nome
        se for encontrado retorna uma fila de Pet com pets que tem o nome de busca. Faz comparação em tres filas;
        se não retorna NULL;
    @params: nome, fila_emergencia,fila_normal,fila_atendidos
*/
Fila* buscarPetNome(char *nome, Fila *fila_emergencia, Fila *fila_normal, Fila *fila_atendidos);
/*  @brief: Busca por Id
        se encontrado retorna o pet com id de busca; se não for retorna NULL;
    @params: id, fila_emergencia, fila_normal, fila_atendidos
*/
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
        fflush(stdin);

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
    printf("\n\t%d | %s ",p->id,nome);
                    /**Perguntar para a lúcia sobre a idade: pode ter 3 digitos?*/
    printf("| %s | %02d | %s | %s ",especie,p->idade,(p->prioridade) ? ("EMERGENCIA") : ("  NORMAL  "), (p->atendido) ? ("        ATENDIDO        ") : ("AGUARDANDO ATENDIMENTO"));
}

void imprimePet(Pet* p)
{
    printf("\n\t%d | %s | %s | %02d | %02d/%02d/%04d | %s\n",p->id,p->nome,p->especie,p->idade,p->data->dia,p->data->mes,p->data->ano,(p->prioridade) ? ("EMERGENCIA") : ("NORMAL"));
}

//função imprimir fila de pets - emergencia e normal
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

//função para imprimir pets da fila de atendidos
void imprimeFilaAtendidos(Fila *fila){
    Nos *aux;
    int maxEspecies = maiorEspecie(fila);
    int max = maiorNome(fila);
    if(!VaziaFila(fila)){
        aux = fila->ini;
        while(aux != NULL){
            imprimePetAtendido(aux->pet,max,maxEspecies);
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

#endif // PET_H_INCLUDED
