#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"
#include <time.h>

#define BLUE 'B'
#define BELLOTA 'S'

int main(){

    juego_t juego;
    
    char movimiento; 
    char personaje = Inicializar_detector_personajes();
    int contador_intentos = 0;
    srand ((unsigned)time(NULL));
    
    inicializar_juego(&juego, personaje);
    
    mostrar_juego(juego);
    

    while(estado_juego(juego) == 0){
        
        scanf(" %c", &movimiento);
        
        if(validacion_tecla(movimiento) == true){
            mover_personaje(&juego, movimiento);
            coordenadas_aleatorias_guardias(&juego);    
        }
        mostrar_juego(juego);
        if(juego.personaje.movimientos <= 0){
            juego.personaje.murio = true;
        }
        if(juego.personaje.murio == true && contador_intentos == 0 && (juego.personaje.tipo == BLUE || juego.personaje.tipo == BELLOTA)){
            juego.personaje.movimientos += 10;
            juego.personaje.murio = false;
            contador_intentos += 1;
        }
        printf("El estado juego es %i.\n", estado_juego(juego));
        if(estado_juego(juego) == -1){
            printf("\n");
            printf("######### TE MORISTE MANCO ########\n");
            return -1;
        }
        if(estado_juego(juego) == 1){
            printf("\n");
            printf("######### GANASTE EL JUEGO NEGRI #########\n");
            return 1;
        }
        
    }
    
    return 0;
}