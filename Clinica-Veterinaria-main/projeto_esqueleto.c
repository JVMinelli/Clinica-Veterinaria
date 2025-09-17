#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct informacoes
{
    int id;
    int idade;
    char Especie[30];
    char Nome[50];
    int prioridade;
}infopet;
typedef struct DataNasci
{
    int dia;
    int mes;
    int ano;
}Data;










int main()
{
    int r=0;
    srand(time(NULL));
    r=100+rand()%900;
    printf("%d", r);
    return 0;
}
