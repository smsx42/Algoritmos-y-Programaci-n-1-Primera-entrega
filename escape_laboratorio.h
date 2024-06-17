#ifndef __ESCAPE_LABORATORIO_H__
#define __ESCAPE_LABORATORIO_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_OBSTACULOS 25
#define MAX_HERRAMIENTAS 25
#define MAX_NIVELES 4
#define MAX_PAREDES 250
#define MAX_DIMENSIONES 17
#define MAX_VACIOS 250

typedef struct coordenada {
	int fil;
	int col;
} coordenada_t;


typedef struct personaje {
	char tipo;
	int movimientos;
	coordenada_t posicion;
	bool tiene_llave;
	bool presiono_interruptor;
	bool murio;
} personaje_t;

typedef struct elemento {
	char tipo;
	coordenada_t posicion;
} elemento_t;

typedef struct nivel {
	coordenada_t entrada;
	coordenada_t salida;

	coordenada_t paredes[MAX_PAREDES];
	int tope_paredes;

	elemento_t obstaculos[MAX_OBSTACULOS];
	int tope_obstaculos;

	elemento_t herramientas[MAX_HERRAMIENTAS];
	int tope_herramientas;
} nivel_t;

typedef struct juego {
	nivel_t niveles[MAX_NIVELES];
	int nivel_actual;
	personaje_t personaje;
} juego_t;

/*
 * Determinará la dimensión de un nivel dado su número 
 * entre 0 y 3 inclusive.
 */

int dimensiones_nivel(int nivel);

/*
 * Inicializará las paredes de un nivel dado el número del nivel, su 
 * vector mapa y su tope.
 */
void inicializar_nivel_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], int numero_nivel, coordenada_t mapa[MAX_PAREDES], int tope);

/* Devolverá la cantidad de monedas correspondientes a un nivel
 * dada una cantidad de baldosas pincho.
 */
int calcular_monedas(int cantidad_pinches);

/* Devolverá la cantidad de paredes de un nivel dada su dimensión y
 *y la matriz del nivel.
 */
int calcular_tope_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], int dimension);

/* Creará una entrada en una posición aleatoria, dado un nivel, la posición de la entrada
 * y la dimensión del nivel.
 */
void crear_entrada(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t *entrada, int dimension);

/* Creará una salida en una posición aleatoria, dado un nivel, la posición de la salida
 * y la dimensión del nivel.
 */
void crear_salida(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t *salida, int dimension);

/* Creará una llave en una posicion aleatoria y llenará tanto el vector de 
 * herramientas como el tope de herramientas, dado un nivel, el vector de herraminetas,
 * la dimensión del nivel y el tope de herramientas.
 */
void crear_llave(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t llave[MAX_HERRAMIENTAS], int dimension, int *tope_herramientas);

/* Creará los teletransportadores en una posicion aleatoria y llenará tanto el vector de 
 * herramientas como el tope de herramientas, dado un nivel, el vector de herraminetas,
 * la dimensión del nivel y el tope de herramientas.
 */
void crear_teletransportadores(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t teletransportadores[MAX_HERRAMIENTAS], int dimension, int cantidad_guardias, int *tope_herramientas);

/* Creará las monedas en una posicion aleatoria y llenará tanto el vector de 
 * herramientas como el tope de herramientas, dado un nivel, el vector de herraminetas,
 * la dimensión del nivel y el tope de herramientas.
 */
void crear_monedas(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t monedas[MAX_HERRAMIENTAS], int dimension, int cantidad_pinchos, int *tope_herramientas);

/* Creará el interruptor en una posicion aleatoria y llenará tanto el vector de 
 * herramientas como el tope de herramientas, dado un nivel, el vector de herraminetas,
 * la dimensión del nivel y el tope de herramientas.
 */
void crear_interruptor(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t interruptor[MAX_HERRAMIENTAS], int dimension, int *tope_herramientas);

/* Creará las baldosas pincho en una posición aleatoria y llenará tanto el vector de 
 * obstáculos como el tope de obstáculos, dado un nivel, el vector de obstáculos,
 * la dimensión del nivel y el tope de obstáculos.
 */
void crear_pinchos(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t pinchos[MAX_HERRAMIENTAS], int dimension, int cantidad_pinchos, int *tope_obstaculos);

/* Creará los guardias en una posición aleatoria y llenará tanto el vector de 
 * obstáculos como el tope de obstáculos, dado un nivel, el vector de obstáculos,
 * la dimensión del nivel y el tope de obstáculos.
 */
void crear_guardias(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t guardia[MAX_OBSTACULOS], int dimension, int cantidad_guardias, int *tope_obstaculos);

/* Creará la bomba en una posición aleatoria y llenará tanto el vector de 
 * obstáculos como el tope de obstáculos, dado un nivel, el vector de obstáculos,
 * la dimensión del nivel y el tope de obstáculos.
 */
void crear_bomba(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], elemento_t bomba[MAX_OBSTACULOS], int dimension, int *tope_obstaculos);

/* llenará tanto el vector de paredes como su tope, dado el vector de coordenadas de paredes, la dimensión del nivel
 * y el tope de paredes.
 */
void guardar_paredes(char nivel[MAX_DIMENSIONES][MAX_DIMENSIONES], coordenada_t paredes[MAX_PAREDES], int dimension, int *tope_paredes);

/*
 * Inicializara un nivel cargando su entrada,
 * salida, obtáculos, herramientas y paredes.
 */
void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba);

/*
 * Inicializará el juego, cargando la informacion de los cuatro niveles
 * y los datos del personaje.
 */
void inicializar_juego(juego_t* juego, char tipo_personaje);

/* Recibe una tecla en donde se devolverá:
 * -> True si la tecla es valida.
 * -> False si la tecla no es valida.
 */
bool validacion_tecla(char tecla);

/* Recibe un juego con todas sus estrucutas validas, la posición del personaje,
 * y la cantidad entera a sumar tanto en fila como columna.
 * Devolverá:
 * -> True si la posición es valida.
 * -> False si la posción no es valida.
 */
bool validacion_coordenada(juego_t juego, coordenada_t posicion, int sumar_fila, int sumar_columna);
/* Recibe un juego con todas sus estructuras validas, el elemento a validar coordenada
 * y su tipo (HERRAMIENTA u OBSTACULO).
 * Devolverá:
 * -> True si la posición es valida.
 * -> False si la posción no es valida.
 */
bool validacion_elementos(juego_t juego, char elemento, char tipo);

/* Recibe un juego con todas sus estructuras validas y la posicion de los guardias
 * en coordenadas del nivel en ejecución.
 * Devolverá:
 * -> True si la posición es valida.
 * -> False si la posción no es valida.
 */
bool validacion_posicion_guardias(juego_t juego, coordenada_t guardias);

/* Recive las coordenadas de la salida del nivel en ejecucion
 * y la posicion del personaje en coordenadas.
 * Devolverá:
 * -> True si la posición es valida.
 * -> False si la posción no es valida.
 */
bool validacion_salida(coordenada_t salida, coordenada_t personaje);

/*
 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo aquello que le sea de
 * utilidad al jugador, como los movimientos restantes,
 * el nivel, los obstáculos posicionados, las paredes, etc.
 */
void mostrar_juego(juego_t juego);

/*
 * Recibe un juego con todas sus estructuras validas y
 * movera al personaje a la ubicacion del proximo teletransportador del que
 * tomo el personaje.
 */
void teletransportar(juego_t *juego);

/* Recibe un juego con todas sus estructuras validas y
 * eliminara la bomba tanto del vector de obstáculos como
 * de la impresión del nivel si la posicion del personaje
 * coincide con la de la bomba, y a su vez, se modificará el tope de obstáculos.
 */
void eliminar_bomba(juego_t *juego);

/* Recibe un juego con todas sus estructuras validas y
 * eliminara la moneda tanto del vector de herramientas como
 * de la impresión del nivel si la posicion del personaje
 * coincide con la de la moneda, y a su vez, se modificará el tope de herramientas.
 */
void eliminar_moneda(juego_t *juego);

/* Recibe un juego con todas sus estructuras validas y
 * eliminara la llave tanto del vector de herramientas como
 * de la impresión del nivel si la posicion del personaje
 * coincide con la de la moneda, y a su vez, se modificará el tope de herramientas.
 */
void eliminar_llave(juego_t *juego);

/* Recibe un juego con todas sus estrucuras validas y
 * cambiará la posición de los guardias.
 */
void coordenadas_aleatorias_guardias(juego_t *juego);

/*
 * Recibe el personaje con todas sus estructuras válidas, y la coordenada de la salida del nivel en ejecución.
 * El nivel se dará por ganado cuando el personaje se
 * posicione en la salida habiendo obtenido previamente la llave.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * ->  1 si el estado es ganado.
 */
int estado_nivel(personaje_t personaje, coordenada_t salida);

/*
 * Recibe un juego con todas sus estructuras válidas.
 * El juego se dará por ganado si el personaje está en el último nivel
 * y posicionado en la salida.
 * El juego se dará por perdido, si el personaje queda sin movimientos.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * -> -1 si el estado es perdido.
 * ->  1 si el estado es ganado.
 */
int estado_juego(juego_t juego);

/*
 * Mueve el personaje en la dirección indicada por el usuario
 * y actualiza el juego según los elementos que haya en el camino
 * del personaje.
 * El juego quedará en un estado válido al terminar el movimiento.
 * El movimiento será:
 * -> w: Si el personaje debe moverse para la arriba.
 * -> a: Si el personaje debe moverse para la derecha.
 * -> s: Si el personaje debe moverse para la abajo.
 * -> d: Si el personaje debe moverse para la izquierda.
 * En caso de que en la dirección que se quiere mover haya una pared
 * se contará como un movimiento, los guardias se moverán y
 * el personaje quedará en la misma baldosa.
 */
void mover_personaje(juego_t* juego, char movimiento);


#endif /* __ESCAPE_LABORATORIO_H__ */
