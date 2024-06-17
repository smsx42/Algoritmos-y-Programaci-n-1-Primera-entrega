#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"
#include <time.h>

#define POLLITO 'P'
#define PURO_HUESO 'H'
#define CORAJE 'C'
#define JOHNNY_BRAVO 'J'
#define BLUE 'B'
#define BELLOTA 'S'


#define MAX_OBSTACULOS 25
#define MAX_HERRAMIENTAS 25
#define MAX_NIVELES 4
#define MAX_PAREDES 250
#define MAX_DIMENSIONES 17
#define MAX_VACIOS 250

const char PERSONAJE = 'J';

const char PARED = '#';
const char VACIO = ' ';
const char BOMBA = 'B';
const char GUARDIA = 'G';
const char PINCHOS = 'P';
const char INTERRUPTOR = 'I';
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char TELETRANSPORTADOR = 'T';
const char MONEDA = 'M';
const char LLAVE = 'L';

const int NIVEL_1 = 0;
const int NIVEL_2 = 1;
const int NIVEL_3 = 2;
const int NIVEL_4 = 3;

const char CANTIDAD_MOVIMIENTOS_INICIALES = 10;
const char SIN_MOVIMIENTOS = 0;

const char HERRAMIENTAS = 'H';
const char OBSTACULOS = 'O';

const char CANTIDAD_PINCHOS_1 = 4;
const char CANTIDAD_PINCHOS_2 = 6;
const char CANTIDAD_PINCHOS_3 = 6;
const char CANTIDAD_PINCHOS_4 = 10;
const char CANTIDAD_GUARDIA_1 = 2;
const char CANTIDAD_GUARDIA_2 = 3;
const char CANTIDAD_GUARDIA_3 = 3;
const char CANTIDAD_GUARDIA_4 = 4;
const bool BOMBA_1 = false;
const bool BOMBA_2 = false;
const bool BOMBA_3 = true;
const bool BOBMA_4 = true;

const char IZQUIERDA = 'a';
const char DERECHA = 'd';
const char ARRIBA = 'w';
const char ABAJO = 's';


int dimensiones_nivel(int nivel){

    int dimension;

    if(nivel == 1 || nivel == 3){
        dimension = 12;
    }
    else{
        dimension = 17;
    }

    return dimension;

}

void inicializar_nivel_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], int numero_nivel, coordenada_t mapa[MAX_PAREDES],int tope){

    int dimension = dimensiones_nivel(numero_nivel);


    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            nivel[i][j] = VACIO;
        }
    }

    for(int i = 0; i < tope; i++){
        nivel[mapa[i].fil][mapa[i].col] = PARED;
    }
}

int calcular_monedas(int cantidad_pinches){

    int contador_monedas = 0;

    for(int i = 0; i < cantidad_pinches; i++){
        if(i % 2){
            contador_monedas += 1;
        }
    }
    return contador_monedas;
}

int calcular_tope_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], int dimension){

    int contador_paredes;

    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(nivel[i][j] == PARED){
                contador_paredes += 1;
            }
        }
    }

    return contador_paredes;
}


void crear_entrada(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t *entrada, int dimension){


    entrada->fil = rand() % dimension;
    entrada->col = rand() % dimension;
    

    while(nivel[entrada->fil][entrada->col] != VACIO){
        entrada->fil = rand() % dimension;
        entrada->col = rand() % dimension;
    } 

    nivel[entrada->fil][entrada->col] = ENTRADA;

}

void crear_salida(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t *salida, int dimension){


    salida->fil = rand() % dimension;
    salida->col = rand() % dimension;
    

    while(nivel[salida->fil][salida->col] != VACIO){
        salida->fil = rand() % dimension;
        salida->col = rand() % dimension;
    } 

    nivel[salida->fil][salida->col] = SALIDA;
}

void crear_llave(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t llave[MAX_HERRAMIENTAS], int dimension, int *tope_herramientas){


    *tope_herramientas = 0;
    
    llave[*tope_herramientas].tipo = LLAVE;
    llave[*tope_herramientas].posicion.fil = rand() % dimension;
    llave[*tope_herramientas].posicion.col = rand() % dimension;

    while(nivel[llave[*tope_herramientas].posicion.fil][llave[*tope_herramientas].posicion.col] != VACIO){
        llave[*tope_herramientas].posicion.fil = rand() % dimension;
        llave[*tope_herramientas].posicion.col = rand() % dimension;
    } 

    nivel[llave[*tope_herramientas].posicion.fil][llave[*tope_herramientas].posicion.col] = LLAVE;
    *tope_herramientas = 1;
}


void crear_teletransportadores(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t teletransportadores[MAX_HERRAMIENTAS], int dimension, int cantidad_guardias, int *tope_herramientas){


    int cantidad_teletransportadores = cantidad_guardias;
    cantidad_teletransportadores += *tope_herramientas;
    int valor_de_i = *tope_herramientas;

    for(int i = valor_de_i; i < cantidad_teletransportadores; i++){
        teletransportadores[i].tipo = TELETRANSPORTADOR;
        teletransportadores[i].posicion.fil = rand() % dimension;
        teletransportadores[i].posicion.col = rand() % dimension;
        while(nivel[teletransportadores[i].posicion.fil][teletransportadores[i].posicion.col] != VACIO){
            teletransportadores[i].posicion.fil = rand() % dimension;
            teletransportadores[i].posicion.col = rand() % dimension;
        }
        *tope_herramientas = i;
        nivel[teletransportadores[*tope_herramientas].posicion.fil][teletransportadores[*tope_herramientas].posicion.col] = TELETRANSPORTADOR;
    }
    
    *tope_herramientas += 1;
}


void crear_monedas(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t monedas[MAX_HERRAMIENTAS], int dimension, int cantidad_pinchos, int *tope_herramientas){


    int cantidad_monedas = calcular_monedas(cantidad_pinchos);
    int valor_i = *tope_herramientas;
    cantidad_monedas += *tope_herramientas;

    for(int i = valor_i; i < cantidad_monedas; i++){
        monedas[i].tipo = MONEDA;
        monedas[i].posicion.fil = rand() % dimension;
        monedas[i].posicion.col = rand() % dimension;
        while(nivel[monedas[i].posicion.fil][monedas[i].posicion.col] != VACIO){
            monedas[i].posicion.fil = rand() % dimension;
            monedas[i].posicion.col = rand() % dimension;
        }
        *tope_herramientas = i;
        nivel[monedas[i].posicion.fil][monedas[i].posicion.col] = MONEDA;
    }

    *tope_herramientas += 1;

}

void crear_interruptor(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t interruptor[MAX_HERRAMIENTAS], int dimension, int *tope_herramientas){


    interruptor[*tope_herramientas].tipo = INTERRUPTOR;
    interruptor[*tope_herramientas].posicion.fil = rand() % dimension; 
    interruptor[*tope_herramientas].posicion.col = rand() % dimension;

    while(nivel[interruptor[*tope_herramientas].posicion.fil][interruptor[*tope_herramientas].posicion.col] != VACIO){
        interruptor[*tope_herramientas].posicion.fil = rand() % dimension; 
        interruptor[*tope_herramientas].posicion.col = rand() % dimension;
    } 
    nivel[interruptor[*tope_herramientas].posicion.fil][interruptor[*tope_herramientas].posicion.col] = INTERRUPTOR;
    *tope_herramientas += 1;

}

void crear_pinchos(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t pinchos[MAX_HERRAMIENTAS], int dimension, int cantidad_pinchos, int *tope_obstaculos){

    int anterior = 0;

    pinchos[0].tipo = PINCHOS;
    pinchos[0].posicion.fil = rand() % dimension;
    pinchos[0].posicion.col = rand() % dimension;
    while(nivel[pinchos[0].posicion.fil][pinchos[0].posicion.col] != VACIO){
        pinchos[0].posicion.fil = rand() % dimension;
        pinchos[0].posicion.col = rand() % dimension;
    }
    nivel[pinchos[0].posicion.fil][pinchos[0].posicion.col] = PINCHOS;

    for(int i = 1; i < cantidad_pinchos; i++){
        
        pinchos[i].tipo = PINCHOS;
        if(nivel[pinchos[anterior].posicion.fil + 1][pinchos[anterior].posicion.col] == VACIO){
            pinchos[i].posicion.fil = pinchos[anterior].posicion.fil + 1;
            pinchos[i].posicion.col = pinchos[anterior].posicion.col;

        }
        else if(nivel[pinchos[anterior].posicion.fil - 1][pinchos[anterior].posicion.col] == VACIO){
            pinchos[i].posicion.fil = pinchos[anterior].posicion.fil - 1;
            pinchos[i].posicion.col = pinchos[anterior].posicion.col;

        }
        else if(nivel[pinchos[anterior].posicion.fil][pinchos[anterior].posicion.col + 1] == VACIO){
            pinchos[i].posicion.fil = pinchos[anterior].posicion.fil;
            pinchos[i].posicion.col = pinchos[anterior].posicion.col + 1;
            
        }
        else if(nivel[pinchos[anterior].posicion.fil][pinchos[anterior].posicion.col - 1] == VACIO){
            pinchos[i].posicion.fil = pinchos[anterior].posicion.fil;
            pinchos[i].posicion.col = pinchos[anterior].posicion.col - 1;
            
        }
        
        nivel[pinchos[i].posicion.fil][pinchos[i].posicion.col] = PINCHOS;
        anterior ++;
    }

    *tope_obstaculos = cantidad_pinchos;


}

void crear_guardias(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t guardia[MAX_OBSTACULOS], int dimension, int cantidad_guardias, int *tope_obstaculos){

    int valor_i = *tope_obstaculos;
    cantidad_guardias += *tope_obstaculos;
    
    for(int i = valor_i; i < cantidad_guardias; i++){
        guardia[i].tipo = GUARDIA;
        guardia[i].posicion.fil = rand() % dimension;
        guardia[i].posicion.col = rand() % dimension;
        while(nivel[guardia[i].posicion.fil][guardia[i].posicion.col] != VACIO){
            guardia[i].posicion.fil = rand() % dimension;
            guardia[i].posicion.col = rand() % dimension;        
        }
        *tope_obstaculos = i;
        nivel[guardia[*tope_obstaculos].posicion.fil][guardia[*tope_obstaculos].posicion.col] = GUARDIA;
    }
    *tope_obstaculos += 1;
    
}


void crear_bomba(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t bomba[MAX_OBSTACULOS], int dimension, int *tope_obstaculos){


    
    bomba[*tope_obstaculos].tipo = BOMBA;
    bomba[*tope_obstaculos].posicion.fil = rand() % dimension;
    bomba[*tope_obstaculos].posicion.col = rand() % dimension;

    while(nivel[bomba[*tope_obstaculos].posicion.fil][bomba[*tope_obstaculos].posicion.col] != VACIO){
        
        bomba[*tope_obstaculos].posicion.fil = rand() % dimension;
        bomba[*tope_obstaculos].posicion.col = rand() % dimension;
    } 

    nivel[bomba[*tope_obstaculos].posicion.fil][bomba[*tope_obstaculos].posicion.col] = BOMBA;
    *tope_obstaculos += 1;
}

void guardar_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t paredes[MAX_PAREDES], int dimension, int *tope_paredes){

    *tope_paredes = 0;
    int contador_paredes = 0;

    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if (nivel[i][j] == PARED){
                paredes[contador_paredes].fil = i;
                paredes[contador_paredes].col = j;
                contador_paredes += 1;
            }
        }
    }

    *tope_paredes = contador_paredes;
    
}



void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba){

    coordenada_t mapa[MAX_PAREDES];


    char tablero[MAX_DIMENSIONES][MAX_DIMENSIONES];
    int tope_paredes = 0;
    int dimension = dimensiones_nivel(numero_nivel);
    

    obtener_paredes(numero_nivel, mapa, &tope_paredes);
    inicializar_nivel_paredes(tablero,numero_nivel, mapa, tope_paredes);

    crear_pinchos(tablero, nivel->obstaculos, dimension, cantidad_baldosas_pinches, &nivel->tope_obstaculos);
    crear_entrada(tablero, &nivel->entrada, dimension);
    crear_salida(tablero, &nivel->salida, dimension);
    
    crear_llave(tablero, nivel->herramientas, dimension, &nivel->tope_herramientas);
    
    crear_guardias(tablero, nivel->obstaculos, dimension, cantidad_guardia, &nivel->tope_obstaculos);
    crear_teletransportadores(tablero, nivel->herramientas, dimension, cantidad_guardia, &nivel->tope_herramientas);
    crear_monedas(tablero, nivel->herramientas, dimension, cantidad_baldosas_pinches, &nivel->tope_herramientas);

    if(hay_bomba == true){
        crear_bomba(tablero, nivel->obstaculos, dimension, &nivel->tope_obstaculos);
        crear_interruptor(tablero, nivel->herramientas, dimension, &nivel->tope_herramientas);
    }

    guardar_paredes(tablero, nivel->paredes, dimension, &nivel->tope_paredes);

}

void inicializar_juego(juego_t* juego, char tipo_personaje){

    inicializar_nivel(&juego->niveles[NIVEL_1], 1, CANTIDAD_PINCHOS_1, CANTIDAD_GUARDIA_1, BOMBA_1);
    inicializar_nivel(&juego->niveles[NIVEL_2], 2, CANTIDAD_PINCHOS_2, CANTIDAD_GUARDIA_2, BOMBA_2);
    inicializar_nivel(&juego->niveles[NIVEL_3], 3, CANTIDAD_PINCHOS_3, CANTIDAD_GUARDIA_3, BOMBA_3); 
    inicializar_nivel(&juego->niveles[NIVEL_4], 4, CANTIDAD_PINCHOS_4, CANTIDAD_GUARDIA_4, BOBMA_4);

    juego->nivel_actual = NIVEL_1 + 1;
    juego->personaje.tipo = tipo_personaje;
    juego->personaje.movimientos = 10000000;
    juego->personaje.tiene_llave = false;
    juego->personaje.presiono_interruptor = false;
    juego->personaje.murio = false;
    juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual - 1].entrada.fil;
    juego->personaje.posicion.col = juego->niveles[juego->nivel_actual - 1].entrada.col; 

}

bool validacion_tecla(char tecla){
     
    
    return (tecla == ARRIBA || tecla == ABAJO || tecla == IZQUIERDA|| tecla == DERECHA);
}

bool validacion_coordenada(juego_t juego, coordenada_t posicion, int sumar_fila, int sumar_columna){


    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
        if((posicion.fil + sumar_fila)  == juego.niveles[juego.nivel_actual - 1].paredes[i].fil && (posicion.col + sumar_columna)== juego.niveles[juego.nivel_actual - 1].paredes[i].col){
            return true;
        }
    }
    return false; 
}

bool validacion_elementos(juego_t juego, char elemento, char tipo){

    if(tipo == HERRAMIENTAS){
        for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++){
            if(juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo == elemento){
                if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col){
                    return true;
                }
            }
        }
    }
    else if(tipo == OBSTACULOS){
        for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_obstaculos; i++){
            if(juego.niveles[juego.nivel_actual - 1].obstaculos[i].tipo == elemento){
                if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col){
                    return true;
                }
            }
        }
    }

    return false;
        
}

bool validacion_posicion_guardias(juego_t juego, coordenada_t guardias){

    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
        if((guardias.fil == juego.niveles[juego.nivel_actual - 1].paredes[i].fil) && (guardias.col == juego.niveles[juego.nivel_actual - 1].paredes[i].col)){
            return true;
        }
    }

    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_obstaculos; i++){
        if((guardias.fil == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil) && (guardias.col == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col)){
            return true;
        }
    }

    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++){
        if((guardias.fil == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil) && (guardias.col == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col)){
            return true;
        }
    }

    if(guardias.fil == juego.personaje.posicion.fil && guardias.col == juego.personaje.posicion.col){
        return true;
    }
    
    return false;
   
}

bool validacion_pared(juego_t juego){

    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
        if((juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual - 1].paredes[i].fil) && (juego.personaje.posicion.col == juego.niveles[juego.nivel_actual - 1].paredes[i].col)){
            return true;
        }
    }

    return false;
}

bool validacion_salida(coordenada_t salida, coordenada_t personaje){

    if(personaje.fil == salida.fil && personaje.col == salida.col){
        return true;
    }
    
    return false;
}

void mostrar_juego(juego_t juego){

    int dimension = dimensiones_nivel(juego.nivel_actual);
    char llenar_nivel[MAX_DIMENSIONES][MAX_DIMENSIONES];

    
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            llenar_nivel[i][j] = VACIO;
        }
    }

    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
        
        llenar_nivel[juego.niveles[juego.nivel_actual - 1].paredes[i].fil][juego.niveles[juego.nivel_actual - 1].paredes[i].col] = PARED;
    }

    llenar_nivel[juego.niveles[juego.nivel_actual - 1].entrada.fil][juego.niveles[juego.nivel_actual - 1].entrada.col] = ENTRADA;
    llenar_nivel[juego.niveles[juego.nivel_actual - 1].salida.fil][juego.niveles[juego.nivel_actual - 1].salida.col] = SALIDA;


    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_obstaculos; i++){
        llenar_nivel[juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col] = juego.niveles[juego.nivel_actual - 1].obstaculos[i].tipo;
    }
    
    for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++){
        llenar_nivel[juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo;
    }

    if(juego.nivel_actual == NIVEL_1 + 1 || juego.nivel_actual == NIVEL_2 + 1){
        juego.personaje.presiono_interruptor = true;
    }
    
    if(juego.personaje.presiono_interruptor == false){
        llenar_nivel[juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.fil][juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.col] = VACIO;
    }
    else{
        llenar_nivel[juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.fil][juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.col] = juego.niveles[juego.nivel_actual - 1].herramientas[0].tipo;
    }

    llenar_nivel[juego.personaje.posicion.fil][juego.personaje.posicion.col] = PERSONAJE;
    
    system("clear");
   
    printf("\n");

    printf("-Iconos- \n");
    printf("\n");
    printf("J: Jugador\n");
    printf("E: Entrada\n");
    printf("S: Salida\n");
    printf("L: Llave (habilita la salida)\n");
    printf("I: Interruptor (muestra la llave)\n");
    printf("M: Moneda (otorga un movimiento)\n");
    printf("P: Baldosa pincho(resta dos movimientos)\n");
    printf("G: Guardia(quita todos los movimientos)\n");
    printf("B: Bomba(quita todos los movimientos)\n");
    printf("####JKLODFAJGOLRKDÑK####\n");
    printf("\n");
    
    if(juego.personaje.presiono_interruptor == true && juego.personaje.tiene_llave == false){
        printf("#### La llave esta en la posicion (%i , %i)\n", juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.fil, juego.niveles[juego.nivel_actual - 1].herramientas[0].posicion.col);
    }
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            printf(" %c", llenar_nivel[i][j]);
        }
        printf(" \n");
    }
    printf("\n");

    printf("Estas en el nivel %i.\n", juego.nivel_actual);

    printf("\n");

    printf("Presione alguna de las siguientes teclas para realizar un movimiento: 'w' (Adelantes),'s' (Abajo),'a' (Izquierda),'d' (Derecha). \n");
    
    printf("\n");

    printf("Su personaje esta en la posicion: (%i, %i).\n", juego.personaje.posicion.fil, juego.personaje.posicion.col);

    printf("\n");

    printf("Te quedan %i movimientos.\n", juego.personaje.movimientos);

    detener_el_tiempo((float) 0.075);

}

void teletransportar(juego_t *juego){

    int tope_teletransportadores = 0;

    coordenada_t teletransportadores[5];
    int final = 0;

    for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_herramientas; i++){
        if(juego->niveles[juego->nivel_actual - 1].herramientas[i].tipo == TELETRANSPORTADOR){
            teletransportadores[tope_teletransportadores].fil = juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil;
            teletransportadores[tope_teletransportadores].col = juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col;
            tope_teletransportadores += 1;
        }
    }

    final = tope_teletransportadores - 1;

    for(int i = 0; i < tope_teletransportadores; i++){
        if(juego->personaje.posicion.fil == teletransportadores[i].fil && juego->personaje.posicion.col == teletransportadores[i].col){
            if(i == final){  
                juego->personaje.posicion.fil = teletransportadores[0].fil;
                juego->personaje.posicion.col = teletransportadores[0].col;
            }
            else if(i < final){
                juego->personaje.posicion.fil = teletransportadores[i + 1].fil;
                juego->personaje.posicion.col = teletransportadores[i + 1].col;
                return;

            }                         
        }
    }
}
void eliminar_bomba(juego_t *juego){

    int tope_aux = juego->niveles[juego->nivel_actual - 1].tope_obstaculos;

    for(int i = 0; i < tope_aux; i++){
        if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == BOMBA){
            int pos_aux = i;
            if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
                while(pos_aux <= (juego->niveles[juego->nivel_actual - 1].tope_obstaculos - 1)){
                    juego->niveles[juego->nivel_actual - 1].obstaculos[pos_aux] = juego->niveles[juego->nivel_actual - 1].obstaculos[pos_aux + 1];
                    pos_aux ++;
                }
            }
            juego->niveles[juego->nivel_actual - 1].tope_obstaculos --;
            
        }
    }
}

void eliminar_moneda(juego_t *juego){

    int tope_aux = juego->niveles[juego->nivel_actual - 1].tope_herramientas;

    for(int i = 0; i < tope_aux ; i++){
        if(juego->niveles[juego->nivel_actual - 1].herramientas[i].tipo == MONEDA){
            int pos_aux = i;
            if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
                while(pos_aux <= (juego->niveles[juego->nivel_actual - 1].tope_herramientas - 1)){
                    juego->niveles[juego->nivel_actual - 1].herramientas[pos_aux] = juego->niveles[juego->nivel_actual - 1].herramientas[pos_aux +1];
                    pos_aux++;
                }
                juego->niveles[juego->nivel_actual - 1].tope_herramientas --;
            }     
        }
    }

}

void eliminar_llave(juego_t *juego){

    if(juego->niveles[juego->nivel_actual - 1].herramientas[0].tipo == LLAVE){
        int pos_aux = 0;
        if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].herramientas[0].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].herramientas[0].posicion.col){
            while(pos_aux <= (juego->niveles[juego->nivel_actual - 1].tope_herramientas - 1)){
                juego->niveles[juego->nivel_actual - 1].herramientas[pos_aux] = juego->niveles[juego->nivel_actual - 1].herramientas[pos_aux + 1];
                pos_aux++;
            }
            juego->niveles[juego->nivel_actual - 1].tope_herramientas --;
        }
    }
}

void coordenadas_aleatorias_guardias(juego_t *juego){

    int dimension = dimensiones_nivel(juego->nivel_actual);

    int tope_guardias = 0;
    int valor_i = 0;

    coordenada_t guardias[5];

    
    for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_obstaculos; i++){
        if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == GUARDIA){
            guardias[tope_guardias].fil = juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil;
            guardias[tope_guardias].col = juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col;
            tope_guardias ++;
            valor_i = i;
        }
    }

    for(int i = 0; i < tope_guardias; i++){
        guardias[i].fil = rand() % dimension;
        guardias[i].col = rand() % dimension;
        while(validacion_posicion_guardias(*juego, guardias[i]) == true){
            guardias[i].fil = rand() % dimension;
            guardias[i].col = rand() % dimension;
 
        }
        juego->niveles[juego->nivel_actual - 1].obstaculos[valor_i].posicion.fil = guardias[i].fil;
        juego->niveles[juego->nivel_actual - 1].obstaculos[valor_i].posicion.col = guardias[i].col;
        valor_i --;
    }
        
}

int estado_nivel(personaje_t personaje, coordenada_t salida){


    if(validacion_salida(salida, personaje.posicion) == true && personaje.tiene_llave == true){
        return 1;
    }

    return 0;
}

int estado_juego(juego_t juego){

    int retorno;

    if((juego.nivel_actual == NIVEL_1 + 1 || juego.nivel_actual == NIVEL_2 + 1 || juego.nivel_actual == NIVEL_3 + 1 || juego.nivel_actual == NIVEL_4 + 1) && juego.personaje.movimientos > 0){
        retorno = 0;
    }
    else if((juego.nivel_actual == NIVEL_1 + 1 || juego.nivel_actual == NIVEL_2 + 1 || juego.nivel_actual == NIVEL_3 + 1 || juego.nivel_actual == NIVEL_4 + 1) && juego.personaje.movimientos <= 0){
        retorno = -1;
    }

    if((juego.nivel_actual == NIVEL_4 + 1) && juego.personaje.movimientos > 0){
        if(estado_nivel(juego.personaje, juego.niveles[juego.nivel_actual - 1].salida) == 1){
            retorno = 1;
        }
    }

    

    return retorno;

}
         

void mover_personaje(juego_t* juego, char movimiento){
    

    juego->personaje.movimientos --;
    while((validacion_coordenada(*juego, juego->personaje.posicion, -1, 0) == false && movimiento == ARRIBA) || (validacion_coordenada(*juego, juego->personaje.posicion, 1, 0) == false && movimiento == ABAJO) 
    || (validacion_coordenada(*juego, juego->personaje.posicion, 0, -1) == false && movimiento == IZQUIERDA) || (validacion_coordenada(*juego,juego->personaje.posicion, 0, 1) == false && movimiento == DERECHA)){
        if(movimiento == ARRIBA){
            juego->personaje.posicion.fil --;
            mostrar_juego(*juego);
        }
        else if(movimiento == ABAJO){
            juego->personaje.posicion.fil ++;
            mostrar_juego(*juego);
        }
        else if(movimiento == IZQUIERDA){
            juego->personaje.posicion.col --;
            mostrar_juego(*juego);
            }
        else if(movimiento == DERECHA){
            juego->personaje.posicion.col ++;
            mostrar_juego(*juego);
        }
        if(estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual - 1].salida) == 1 && juego->nivel_actual < NIVEL_4 + 1){ 
            juego->nivel_actual ++;
            juego->personaje.movimientos += 10;
            juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual - 1].entrada.fil;
            juego->personaje.posicion.col = juego->niveles[juego->nivel_actual - 1].entrada.col;
            juego->personaje.tiene_llave = false;
            juego->personaje.presiono_interruptor = false;
            mostrar_juego(*juego);
            break;
        }
        if(validacion_elementos(*juego, PINCHOS, OBSTACULOS) == true && juego->personaje.tipo != POLLITO && juego->personaje.tipo != PURO_HUESO){
            juego->personaje.movimientos -= 2; 
        }
        if(validacion_elementos(*juego, BOMBA, OBSTACULOS) == true){
            juego->personaje.murio = true;    
            juego->personaje.movimientos = 0;
            eliminar_bomba(&(*juego));
            mostrar_juego(*juego);
        }
        if(validacion_elementos(*juego, GUARDIA, OBSTACULOS) == true && juego->personaje.tipo != CORAJE && juego->personaje.tipo != JOHNNY_BRAVO){
            juego->personaje.movimientos = 0;
            juego->personaje.murio = true;
            mostrar_juego(*juego);
            break;
        }
        if(validacion_elementos(*juego, MONEDA, HERRAMIENTAS) == true){
            eliminar_moneda(&(*juego));
            juego->personaje.movimientos += 1;
        }
        if(validacion_elementos(*juego, TELETRANSPORTADOR, HERRAMIENTAS) == true){
            teletransportar(&(*juego));
            mostrar_juego(*juego);
            break;
        }
        if(validacion_elementos(*juego, INTERRUPTOR, HERRAMIENTAS) == true){
            juego->personaje.presiono_interruptor = true;
            mostrar_juego(*juego);    
        }
        if(validacion_elementos(*juego, LLAVE, HERRAMIENTAS) == true){
            juego->personaje.tiene_llave = true;
            eliminar_llave(&(*juego));
        }
        if(estado_juego(*juego) == 1){
            return;

        }

    }

}


