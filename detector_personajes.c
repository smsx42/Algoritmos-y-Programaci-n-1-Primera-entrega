#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "detector_personajes.h"
#include "escape_laboratorio.h"

char const DULCE = 'D';
char const AMARGO = 'A';
char const SALADO = 'S';

char const AZUL = 'A';
char const AMARILLO = 'Y';
char const VERDE = 'V';
char const NEGRO = 'N';
char const BLANCO = 'B';
char const ROSA = 'R';

char const CORAJE = 'C';
char const JOHNNY = 'J';
char const POLLITO = 'P';
char const PURO_HUESO = 'H';
char const BELLOTA = 'S';
char const BLUE = 'B';

int const ALTURA_J0HNNY = 180;
int const ALTURA_BELLOTA = 120;
int const ALTURA_POLLITO = 50;
int const ALTURA_BLUE = 140;
int const ALTURA_HUESO = 200;
int const ALTURA_CORAJE = 30;

int const ALTURA_MINIMA = 10;
int const ALTURA_MAXIMA = 250;

int const MINIMO_PUNTAJE_PAREJA_1 = 1;
int const MAXIMO_PUNTAJE_PAREJA_1 = 80;
int const MINIMO_PUNTAJE_PAREJA_2 = 81;
int const MAXIMO_PUNTAJE_PAREJA_2 = 160;
int const MINIMO_PUNTAJE_PAREJA_3 = 161;
int const MAXIMO_PUNTAJE_PAREJA_3 = 240;

int const MINIMA_FECHA_VALIDA = 1988;
int const MAXIMA_FECHA_VALIDA = 2008;

int const MINIMA_TALLA_VALIDA = 33;
int const SEGUNDA_TALLA = 37;
int const TERCER_TALLA = 38;
int const CUARTA_TALLA = 42;
int const QUINTA_TALLA = 43;
int const MAXIMA_TALLA_VALIDA = 47;
int const TALLA_NULA = 0;

int const PUNTAJE_SALADO = 5;
int const PUNTAJE_DULCE = 15;
int const PUNTAJE_AMARGO = 20;

int const TALLA_1 = 1;
int const TALLA_2 = 2;
int const TALLA_3 = 3;
int const TALLA_4 = 4;

int const PUNTAJE_ROSA_AMARILLO = 5;
int const PUNTAJE_NEGRO_BLANCO = 15;
int const PUNTAJE_AZUL_VERDE = 20;

void Imprimir_fecha(){
    printf("Cuál es la fecha de nacimineto entre 1988 y 2008 (incluyendo ambos)?\n");
}

void Imprimir_sabor(){
    printf("Cuál es su sabor favorito, entre Salado (S), Dulce (D) y Amargo (A)?\n");
}

void Imprimir_talla(){
    printf("Cuál es la talla de zapatos entre 33 y 47 (incluyendo ambos) y 0 si mo usa zapatos?\n");
}

void Imprimir_color(){
    printf("Cuál es su color favorito, entre Azul (A), Amarillo (Y), Rosa (R), Blanco (B), Negro (N), y Verde (V)?\n");
}

void Imprimir_altura(){
    printf("Cuál es la altura entre los 10 y 250 cms (incluyendo ambos)?\n");
}

bool Validacion_fecha(int fecha_valida){

    
    return (fecha_valida >= MINIMA_FECHA_VALIDA && fecha_valida <= MAXIMA_FECHA_VALIDA);

}

bool Validacion_sabor(char sabor_valido){
    
    bool retorno;

    if (sabor_valido != SALADO &&
        sabor_valido != DULCE &&
        sabor_valido != AMARGO){
            retorno = false;
        }
    else{
        retorno = true;
    }
    return retorno;
}

bool Validacion_talla(int talla_valida){
    
    return ((talla_valida >= MINIMA_TALLA_VALIDA && talla_valida <= MAXIMA_TALLA_VALIDA) || talla_valida == TALLA_NULA);
}

bool Validacion_color(char color_valido){

    bool retorno;
    
    if (color_valido != AZUL &&
        color_valido != AMARILLO &&
        color_valido != VERDE &&
        color_valido != NEGRO &&
        color_valido != BLANCO &&
        color_valido != ROSA){
            retorno = false;
        }
    else{
        retorno = true;
    }
    return retorno;
}

int Puntaje_total(int puntaje_comida,int puntaje_color,int  puntaje_ano,int multiplicador_talla){

    int puntaje_total = (puntaje_comida + puntaje_color + puntaje_ano) * multiplicador_talla;
    
    printf("El puntaje_total es de %i.\n", puntaje_total);
    
    return puntaje_total;
}

bool Validacion_altura(int altura_valida){

    return (altura_valida >= ALTURA_MINIMA && altura_valida <= ALTURA_MAXIMA);
}

int Calcular_anio(int * fecha_nacimiento){
 
    system("clear"); 
    Imprimir_fecha();
    scanf("%i", &(*fecha_nacimiento));

    int puntaje_anio;

    while(Validacion_fecha(*fecha_nacimiento) == false){
        printf("Esta no es una fecha valida, vuelva a intentarlo.\n");
        Imprimir_fecha();
        scanf("%i", &(*fecha_nacimiento));
    }
    
    return (puntaje_anio = (*fecha_nacimiento % 20) + 1);
}

int Calcular_sabor(char * sabor){

    int puntaje_comida;

    Imprimir_sabor();
    scanf(" %c", &(*sabor));
    
    while (Validacion_sabor(*sabor) == false){
        printf("Ese sabor no es valido, vuelva a intentarlo.\n");
        Imprimir_sabor();
        scanf(" %c", &(*sabor));
    }
    if (*sabor == SALADO){
        puntaje_comida = PUNTAJE_SALADO;
    }
    else if (*sabor == DULCE){
        puntaje_comida = PUNTAJE_DULCE;
    }
    else if (*sabor == AMARGO){
        puntaje_comida = PUNTAJE_AMARGO;
    }

    return puntaje_comida;
    
}

int Calcular_talla(int * talla){

    int multiplicador_talla;

    Imprimir_talla();
    scanf("%i", &(*talla));
    
    while(Validacion_talla(*talla) == false){
        printf("La talla ingresada no es valida, vuevla a intentarlo.\n");
        Imprimir_talla();
        scanf("%i", &(*talla));
    }
    if (*talla == TALLA_NULA){
        multiplicador_talla = TALLA_1;
    }
    else if (*talla >= MINIMA_TALLA_VALIDA && *talla <= SEGUNDA_TALLA){
        multiplicador_talla = TALLA_2;
    }
    else if (*talla >= TERCER_TALLA && *talla <= CUARTA_TALLA){
        multiplicador_talla = TALLA_3;
    }
    else if (*talla >= QUINTA_TALLA && *talla <= MAXIMA_TALLA_VALIDA){
        multiplicador_talla = TALLA_4;
    }

    return multiplicador_talla;
}

int Calcular_color(char * color){

    int puntaje_color;

    Imprimir_color();
    scanf(" %c", &(*color));
    
    while(Validacion_color(*color) == false){
        printf("Ese color no es valido, vuevla a intentarlo.\n");
        Imprimir_color();
        scanf(" %c", &(*color));
    }
    if (*color == ROSA || *color == AMARILLO){
        puntaje_color = PUNTAJE_ROSA_AMARILLO;
    }
    else if (*color == NEGRO || *color == BLANCO){
        puntaje_color = PUNTAJE_NEGRO_BLANCO;
    }
    else if (*color == AZUL || *color == VERDE){
        puntaje_color = PUNTAJE_AZUL_VERDE;    
    }

    return puntaje_color;   

}

int Calcular_altura(int * altura){

    Imprimir_altura();
    scanf("%i", &(*altura));
   
    while(Validacion_altura(*altura) == false){
        printf("La altura ingresada no es valida, vuevla a intentarlo.\n");
        Imprimir_altura();
        scanf("%i", &(*altura));
    }

    return *altura;

}

void Imprimir_puntajes(int puntaje_color, int puntaje_comida, int puntaje_anio, int multiplicador_talla){

    printf("El puntaje_color es de %i.\n", puntaje_color);
    
    printf("\n");
    
    printf("El puntaje_comida es de %i.\n", puntaje_comida);
    
    printf("\n");

    printf("El puntaje_anio es de %i.\n", puntaje_anio);
    
    printf("\n");

    printf("El multiplicador_talla es de %i.\n", multiplicador_talla);

    printf("\n");
}

char Determinar_personaje (int puntaje_total, int altura){

    char es_personaje;

    if (puntaje_total >= MINIMO_PUNTAJE_PAREJA_1 && puntaje_total <= MAXIMO_PUNTAJE_PAREJA_1){
        int diferencia_personaje_1 = abs(ALTURA_J0HNNY - altura);
        int diferencia_personaje_2 = abs(ALTURA_CORAJE - altura);
        if (diferencia_personaje_1 > diferencia_personaje_2){
            printf("Entonces, el personaje podria ser - Coraje -.\n");
            printf("\n");
            es_personaje = CORAJE;
        }
        else if (diferencia_personaje_2 >= diferencia_personaje_1){
            printf("Entonces, el personaje podria ser - Johnny Bravo -.\n");
            printf("\n");
            es_personaje = JOHNNY;
        }

    }
    else if(puntaje_total >= MINIMO_PUNTAJE_PAREJA_2  && puntaje_total <= MAXIMO_PUNTAJE_PAREJA_2){
        int diferencia_personaje_1 = abs(ALTURA_HUESO - altura);
        int diferencia_personaje_2 = abs(ALTURA_POLLITO - altura);
        if (diferencia_personaje_1 > diferencia_personaje_2){
            printf("Entonces, el personaje podria - Pollito -.\n");
            printf("\n");
            es_personaje = POLLITO;
        }
        else if (diferencia_personaje_2 >= diferencia_personaje_1){
            printf("Entonces, el personaje podria - Puro Hueso -.\n");
            printf("\n");
            es_personaje = PURO_HUESO;
        }

    }
    else if (puntaje_total >= MINIMO_PUNTAJE_PAREJA_3 && puntaje_total <= MAXIMO_PUNTAJE_PAREJA_3){
        int diferencia_personaje_1 = abs(ALTURA_BLUE - altura);
        int diferencia_personaje_2 = abs(ALTURA_BELLOTA - altura);
        if (diferencia_personaje_1 > diferencia_personaje_2){
            printf("Entonces, el personaje podria ser - Bellota -.\n");
            printf("\n");
            es_personaje = BELLOTA;
        }
        else if (diferencia_personaje_2 >= diferencia_personaje_1){
            printf("Entonces, el personaje podria ser - Blue -.\n");
            printf("\n");
            es_personaje = BLUE;
        }

    }   

    return es_personaje;

}           
char Inicializar_detector_personajes(){

    int fecha_nacimiento;
    char sabor;
    int talla;
    char color;
    int altura;

    
    int puntaje_comida;
    int puntaje_color;
    int puntaje_anio;
    int multiplicador_talla;
    int puntaje_total;
    int calculo_altura;

    char tecla;
    
    
    printf("Dado los valores elegidos por el usuario, debe mostrar por pantalla la puntuación total y el personaje elejido.\n");

    puntaje_anio = Calcular_anio(&fecha_nacimiento);

    system("clear");

    puntaje_comida = Calcular_sabor(&sabor);

    system("clear");

    multiplicador_talla = Calcular_talla(&talla);

    system("clear");

    puntaje_color = Calcular_color(&color);

    system("clear");
    
    altura = Calcular_altura(&calculo_altura);

    system("clear");
    
    Imprimir_puntajes(puntaje_color, puntaje_comida, puntaje_anio, multiplicador_talla);

    
    puntaje_total = Puntaje_total(puntaje_comida, puntaje_color, puntaje_anio, multiplicador_talla);

    printf("\n");

    
    char personaje = Determinar_personaje(puntaje_total, altura);

    if(personaje == BLUE){
        printf("-Habilidad: si moris revivis con 10 intentos. \n");
    }
    else if(personaje == BELLOTA){
        printf("-Habilidad: si moris revivis con 10 intentos. \n");
    }
    else if(personaje == CORAJE){
        printf("-Habilidad: no te agarran los guardias. \n");
    }
    else if(personaje == JOHNNY){
        printf("-Habilidad: no te agarran los guardias. \n");
    }
    else if(personaje == POLLITO){
        printf("-Habilidad: no te afectan las baldosas pinchos. \n");
    }
    else if(personaje == PURO_HUESO){
        printf("-Habilidad: no te afectan las baldosas pinchos. \n");
    }
    
    printf("\n");
    printf("Presione cualquier tecla para empezar a jugar.\n");
    scanf(" %c", &tecla);


    return personaje;
}
