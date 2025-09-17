#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PET.h"
#include "FILA.h"
#include <ctype.h>


int main(){
    Fila *fila_normal = CriaFila();
    Fila *fila_emergencia = CriaFila();
    Fila *fila_atendidos = CriaFila();
    srand(time(NULL));
    InsereFila(fila_normal,criaPet(fila_normal,fila_emergencia,fila_atendidos));
    imprimePet(fila_normal->ini->pet);
    scanf("%d");
}
