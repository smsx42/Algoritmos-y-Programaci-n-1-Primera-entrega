#ifndef DETECTOR_PERSONAJES_H
#define DETECOR_PERSONAES_H
#include <stdbool.h>



/*Imprime por pantalla el rango valido al que debe pertenecer  los años.
*/
void Imprimir_fecha();

/*Imrpime por pantalla las opciones validas para los sabores.
*/
void Imprimir_sabor();

/*Imprime por pantalla el rango valido al que debe pertencer la talla de zapatos.
*/
void Imprimir_talla();

/*Imprime por pantalla las opciones validas para los colores.
*/
void Imprimir_color();

/*Imprime por pantalla el rango valido de la altura.
*/
void Imprimir_altura();


/*Devuelve un valor booleano dependinedo de si se cumplen o no las condiciones dadas.
*/
bool Validacion_fecha(int fecha_valida);

/*Devuelve un valor booleano dependinedo de si se cumplen o no las condiciones dadas.
*/
bool Validacion_sabor(char sabor_valido);

/*Devuelve un valor booleano dependinedo de si se cumplen o no las condiciones dadas.
*/
bool Validacion_talla(int talla_valida);


/*Devuelve un valor booleano dependinedo de si se cumplen o no las condiciones dadas.
*/
bool Validacion_color(char color_valido);

/*Devuelve e imprime por pantalla el puntaje total, dados los distitnos puntajes
 *y el multiplicador de talla.
*/
int Puntaje_total(int puntaje_comida,int puntaje_color,int  puntaje_ano,int multiplicador_talla);

/*Devuelve un valor booleano dependinedo de si se cumplen o no las condiciones dadas.
*/
bool Validacion_altura(int altura_valida);

/*Devuelve el puntaje total del año.
*/
int Calcular_anio(int * fecha_nacimiento);


/*Devuelve el puntaje total del sabor.
*/
int Calcular_sabor(char * sabor);


/*Devuelve el puntaje total de la talla.
*/
int Calcular_talla(int * talla);



/*Devuelve el puntaje total del color.
*/
int Calcular_color(char * color);


/*-Devuelve la altura.
*/
int Calcular_altura(int * altura);


/*Imprime los puntajes totaltes de cada categoria.
*/
void Imprimir_puntajes(int puntaje_color, int puntaje_comida, int puntaje_anio, int multiplicador_talla);


/*Devuelve al personaje en funcion del puntaje total y la altura ingresada.
*/
char Determinar_personaje (int puntaje_total, int altura);


/*Inicializa el programa detecor de personajes.
*/
char Inicializar_detector_personajes();

#endif /* __DETECTOR_PERSONAJES_H__ */



