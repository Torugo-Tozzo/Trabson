


#ifndef FILA_H
#define FILA_H

#include "lista.h"

typedef tLista tFila;

inline tFila* inicia_fila(){
    return inicia_lista();
};

inline tFila * encerra_fila(tFila * p){
    return encerra_lista(p);
};

inline void in_BD(tFila * p){
    inicia_BD(p);
};

inline void insere_fila(tFila * p){
    insere_inicio(p);
};

inline no * remove_fila(tFila * p){
    return remove_fim(p);
};

inline void  print_fila(tFila * p){
   imprime(p);
};

inline void  filainsere(no * topo, tFila* fim){
  inserir(topo,fim);  
};

#endif /* LISTA_H */