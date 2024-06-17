#ifndef FUNCIONES_FOSTER_H

#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200
#define MAX_AMIGOS 100





/* Muestra por pantalla las especificaciones que debe cumplir un amigo.
*/
void imprimir_seleccionados(lista_ninio_t ninio);

/* Modifica el estado del amigo.
 * Devuelvera -1 en el caso de que no se halla podido leer el archuvi y 
 * devolvera false(-1) en el caso de que se halla elegido a un amigo.
*/  
int modificar_estado(amigo_t amigo, long unsigned int retorno);

/* Determina e informa al usuario el amigo imaginario dependiendo las especificaciones dadas por el niño.
 * Devolvera -1 en el caso de que no se halla elegido a ningun amigo, y se devolvera una valor de retorno si
 * se eligio al amigo.
*/
int elegir_amigo(amigo_t amigo, los_elegidos_t seleccionados[MAX_AMIGOS], numero_amigo_t amigo_posicion[MAX_AMIGOS], int tope_posicion, int tope_amigos_seleccionados, char nuevo_amigo[MAX_NOMBRE]);

/* Crea un archivo binario en forma de lista con todas las caracteristicas de los amigos imaginarios de la mansion.
 * Devolvera -1 en el caso de que no se halla podido crear el archvio y 
 * devolvera 0  en el caso de que se halla podido crear.
*/
int escribir_amigo_mansion();

/* Le pregunta al usuario las especificaciones que debe tener el amigo para ser adoptado y los amigos
 * que tubo el niño; creara una un archivo de texto con dichas 
 * especificacions y listara a los amigos que tuvo el niño.
 * Devolvera -1 si no se pudo crear el archivo, y devolvera 0 si se puedo crear.
*/
int escribir_lista_ninio();

/* Imprime por pantalla una lista con todos los amigos del arhivo.dat, devuelve -1 si no se
 * pudo leer el arhcivo y 1 si se pudo imprimir.
 */ 
int listar_amigos();

/* Imprime por pantalla todas las especificaciones del niño y los nombres de los ex amigos, devuelve
 * -1 si no se pudo leer el archivo.txt y 1 si se pudo mostrar.
 */
int lista_ninio();

/* Determina y devuelve el nombre de un amigo imaginario perteneciante a la lista de amigos, si se cumplen todas especificaciones.
*/
int determinar_amigo();

#endif /* __FUNCIONES_FOSTER_H__ */