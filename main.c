#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PET.h"
#include "FILA.h"
#include <locale.h>
#include <string.h>

#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

#define PASS COLOR_GREEN "[SUCESSO]" COLOR_RESET
#define FAIL COLOR_RED "[FALHA]" COLOR_RESET
#define INFO COLOR_YELLOW "[INFO]" COLOR_RESET

int main(){

    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    /** Crias filas de atendimento*/
    Fila *fila_normal = CriaFila();
    Fila *fila_emergencia = CriaFila();
    /** Fila de pets já atendidos*/
    Fila *fila_atendidos = CriaFila();

    const char* inicio1 = "\n=========================================================\n";
    const char* inicio2 = "\n===   Sistema de Gerenciamento - Clinica Veterinária  ===\n";
    const char* inicio3 = "\n=========================================================\n";
    const char* dog1 = "\n           / __";
    const char* dog2 = "\n          (    @ ___";
    const char* dog3 = "\n          /         O";
    const char* dog4 = "\n         /   (_____/";
    const char* dog5 = "\n        /____/   U";
    const char* bem_vindo = "\nBem-vindo! Por favor, escolha uma opção: \n";
    const char* opcoes = "\n[1] Adicionar Pet a Fila de Atendimento \n[2] Chamar Proximo Pet para Atendimento \n[3] Buscar Pet (por ID ou Nome) \n[4] Listar Pets na Fila de Espera \n[5] Ver Proximo Pet da Fila \n[6] Listar Pets ja Atendidos \n[7] Sair do Sistema \n\n\t>> Sua escolha:";

    int operacao;
    printf("%s",inicio1);
    printf("%s",inicio2);
    printf("%s",inicio3);
    printf("%s",dog1);
    printf("%s",dog2);
    printf("%s",dog3);
    printf("%s",dog4);
    printf("%s",dog5);
    printf("%s",bem_vindo);
    printf("%s",opcoes);
    scanf("%d", &operacao);
    fflush(stdin);

    while(operacao!=7){
        switch(operacao){
        case 1:
            Pet *pet = criaPet(fila_normal,fila_emergencia,fila_atendidos);
            if(pet != NULL){
                printf("\n\t%s Pet %s (ID: %d) adicionado a fila de %s.",PASS,pet->nome,pet->id,(pet->prioridade) ? ("EMERGENCIA") : ("NORMAL"));
            }
            else{
                printf("\n\t%s Não foi possivel cadastrar o pet",FAIL);
            }
            if(pet->prioridade == 1){
                InsereFila(fila_emergencia, pet);
            }
            else{
                InsereFila(fila_normal, pet);
            }
            break;
        case 2:
            if(VaziaFila(fila_emergencia)){
                if(VaziaFila(fila_normal)){
                    printf("\n%s Nao ha pets na fila de espera.", INFO);
                }
                else{
                    Pet *petAux = RetiraFila(fila_normal);
                    petAux->atendido = 1;
                    InsereFila(fila_atendidos, petAux);
                    printf("\n%s O pet %s foi atendido e removido da fila.",PASS,petAux->nome);
                    imprimePetAtendido(petAux,strlen(petAux->nome));
                }
            }
            else{
                Pet *petAux = RetiraFila(fila_emergencia);
                petAux->atendido = 1;
                InsereFila(fila_atendidos, petAux);
                printf("\n%s O pet %s foi atendido e removido da fila.",PASS,petAux->nome);
                imprimePetAtendido(petAux,strlen(petAux->nome));
            }
            break;

        case 3:
            int a = -1;
            do{
                printf("Deseja buscar o pet por nome(0) ou por Id(1)?: ");
                scanf("%d", &a);
                while (getchar() != '\n');
            }while(a!=0 && a!=1);

            if(a == 0){
                printf("Qual o nome do pet? ");
                char nome[50];
                fflush(stdin);
                fgets(nome,sizeof(nome),stdin);
                nome[strcspn(nome, "\n")] = '\0';
                fflush(stdin);

                Fila *nomes = buscarPetNome(nome, fila_emergencia, fila_normal, fila_atendidos);
                if(!VaziaFila(nomes)){
                    imprimeFilaAtendidos(nomes);
                }
                else{
                    printf("%s Nenhum pet com esse nome foi encontrado!\n", INFO);
                }
            }
            if(a == 1){
                printf("Qual o id do pet?");
                int id;
                scanf("%d", &id);

                Pet *petId = buscarPetId(id, fila_emergencia, fila_normal, fila_atendidos);
                if(petId != NULL){
                    imprimePetAtendido(petId,strlen(petId->nome));
                }
                else{
                    printf("%s Nenhum pet com esse id foi encontrado!\n",INFO);
                }
            }

            break;

        case 4:
            printf("\nfila de emergência: \n");
            imprimeFila(fila_emergencia);
            printf("\nfila de normal: \n");
            imprimeFila(fila_normal);
            break;

        case 5:
            if(VaziaFila(fila_emergencia)){
                if(VaziaFila(fila_normal)){
                    printf("Fila vazia");
                }
                else{
                    imprimePet(fila_normal->ini->pet);
                }
            }
            else{
                imprimePet(fila_emergencia->ini->pet);
            }

            break;

        case 6:
            if(VaziaFila(fila_atendidos)){
                printf("%s Nenhum pet foi atendido!",FAIL);
            }
            else{
                imprimeFilaAtendidos(fila_atendidos);
            }
            break;

        case 7:
            printf("\n%s Muito Obrigado!\n", INFO);
            return 0; //exit(0);
            break;

        default:
            printf("%s Opção invalida, digite uma opção valida\n",FAIL);
            break;
        }
        printf("\n");
        system("pause");
        system("cls");
        printf("%s",inicio1);
        printf("%s",inicio2);
        printf("%s",inicio3);
        printf("%s",dog1);
        printf("%s",dog2);
        printf("%s",dog3);
        printf("%s",dog4);
        printf("%s",dog5);
        printf("%s",bem_vindo);
        printf("%s",opcoes);
        scanf("%d", &operacao);
    }
    printf("\n%s Muito Obrigado!\n", INFO);
}
