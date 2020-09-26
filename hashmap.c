#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    long posicion = hash(key, map->capacity);//Se obtiene la posicion (a)
    while(map->buckets[posicion] != NULL){
      posicion ++; //Resolucion colisiones (b)
      if(posicion == map->capacity){
      posicion = 0; //Caso de que llegue al final del arreglo, recorre denuevo el arreglo
      }
    }
  
    // int capacidadmax = (0.7 * map->capacity);
    // Hacer if para aumentar el tamaño del arreglo(enlarge)

    map->buckets[posicion] = createPair(key, value); //Ingresa el par en la casilla (c)
    map->current = posicion; //Actualiza el current
    map->size++; //Aumenta size ya que se agrega un elemento
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **) calloc (10,sizeof(Pair *));
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

void * searchMap(HashMap * map,  char * key) {   
    long posicion = hash(key, map->capacity);//Se obtiene la posicion (a)
    while(is_equal(map->buckets[posicion]->key, key) == 0){
      posicion++; //Avanza si no encuentra la clave(b)
      if(map->buckets[posicion] == NULL){
        return NULL; //LLega a casilla nula, retorna NULL
      }
      if(posicion == map->capacity){
      posicion = 0; //Caso de que llegue al final del arreglo
      }
    }

    if(is_equal(map->buckets[posicion]->key, key) == 1){ //Si encuentra la key
      map->current = posicion; //Actualiza current
      return map->buckets[posicion]->value; //Retorna valor de la clave
    }
    return NULL;
}

void * firstMap(HashMap * map) {
    long posicion = 0; //Se inicializa en 0 para recorrer el arreglo
    while((map->buckets[posicion] == NULL) || (map->buckets[posicion]->key == NULL)){
      posicion++; //Si es que no existe un value se sigue iterando
    }
    map->current = posicion; //Actualiza current
    return map->buckets[posicion]->value; //Retorna primer valor que encuentra
}

void * nextMap(HashMap * map) {
    int posSig = map->current+1;
    while(map->buckets[posSig]->key == NULL){
      posSig++; //Si es que no existe un value se sigue iterando
    }
    map->current = posSig;
    return map->buckets[posSig]->value;
}
