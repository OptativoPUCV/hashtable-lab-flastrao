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
      posicion = 0; //Caso de que llegue al final del arreglo

      }
    }
  
    // int capacidadmax = (0.7 * map->capacity);
    // Hacer if para aumentar el tamaño del arreglo

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

    while(is_equal(map->buckets[posicion]->key, key)){
      posicion++; //Avanza si no encuentra la clave(b)
      if(map->buckets[posicion] == NULL){
        return NULL; //LLega a casilla nula, retorna NULL
      }
      if(map->buckets[posicion]->key == key){
        return map->buckets[posicion]->value; //Retorna valor de la clave
      }
    }
    map->current = posicion; //Actualiza current

    return NULL;
}

void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}
