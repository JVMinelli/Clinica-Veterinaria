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

    const char* bem_vindo = "Bem-Vindo\n";
    const char* opcoes = "Escolha uma opção: \n\t 1.Inserir um pet na fila de atendimento \n\t 2.Atender pet \n\t 3.Busca pet por id ou nome \n\t 4.Imprimir Pets a serem atendidos \n\t 5.Imprimir próximo pet a ser atendido \n\t 6.Imprimir pet já atendidos \n\t 7.Sair \n";
    int operacao;
    printf("%s",bem_vindo);
    printf("%s",opcoes);
    scanf("%d", &operacao);
    while(operacao!=7){
        switch(operacao){
        case 1:
            Pet *pet = criaPet(fila_normal,fila_emergencia,fila_atendidos);
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
                    printf("Fila vazia");
                }
                else{
                    Pet *petAux = RetiraFila(fila_normal);
                    petAux->atendido = 1;
                    InsereFila(fila_atendidos, petAux);
                }
            }
            else{
                Pet *petAux = RetiraFila(fila_emergencia);
                petAux->atendido = 1;
                InsereFila(fila_atendidos, petAux);
            }
            break;

        case 3:
            int a;
            printf("Deseja buscar o pet por nome(0) ou por Id(1)?: ");
            scanf("%d", &a);

            if(a == 0){
                printf("Qual o nome do pet?");
                char nome[50];
                scanf("%s", &nome);

                Fila *nomes = buscarPetNome(nome, fila_emergencia, fila_normal, fila_atendidos);
                if(!VaziaFila(nomes)){
                    imprimeFilaAtendidos(nomes);
                }
                else{
                    printf("nenhum pet com esse nome foi encontrado!\n");
                }
            }
            if(a == 1){
                printf("Qual o id do pet?");
                int id;
                scanf("%d", &id);

                Pet *petId = buscarPetId(id, fila_emergencia, fila_normal, fila_atendidos);
                if(!petId == NULL){
                    imprimePetAtendido(petId);
                }
                else{
                    printf("nenhum pet com esse id foi encontrado!\n");
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
                printf("Nenhum pet foi atendido!");
            }
            else{
                imprimeFilaAtendidos(fila_atendidos);
            }
            break;

        case 7:
            return 0; //exit(0);
            break;

        default:
            printf("opção invalida, digite uma opção valida\n");
            break;
        }
        printf("%s",opcoes);
        scanf("%d", &operacao);
    }


}
