#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PET.h"
#include "FILA.h"
#include <locale.h>

int main(){

    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    /** Crias filas de atendimento*/
    Fila *fila_normal = CriaFila();
    Fila *fila_emergencia = CriaFila();
    /** Fila de pets já atendidos*/
    Fila *fila_atendidos = CriaFila();

    const char* bem_vindo = "Bem-Vindo";
    const char* opcoes = "Escolha uma opção: \n\t 1.Inserir um  pet na fila de atendimento \n\t 2.Atender pet \n\t 3.Busca pet por id ou nome \n\t 4.Imprimir Pets a serem atendidos \n\t 5.Imprimir próximo pet a ser atendido \n\t 6.Imprimir pet já atendidos \n\t 7.Sair";
    int operacao;
    printf("%s",opcoes);
    scanf("%d",operacao);
    while(opcao_escolhida!=7){
        switch(operacao){
        case 1:

        }
    }


}
