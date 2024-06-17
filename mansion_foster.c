#include "funciones_foster.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){

    if(strcmp(argv[1], "listar_amigos") == 0){
        listar_amigos();
    }

    if(strcmp(argv[1], "lista_ninio") == 0){
        lista_ninio();
    }

    if(strcmp(argv[1], "determinar_amigo") == 0){
        determinar_amigo();
    }

    if(strcmp(argv[1], "Escribir_amigo_mansion") == 0){
        escribir_amigo_mansion();
    }

    if(strcmp(argv[1], "Escribir_lista_ninio") == 0){
        escribir_lista_ninio();
    }
    
    return 0;
}