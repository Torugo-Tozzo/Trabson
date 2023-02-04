/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   fila.h
 * Author: 2022.1.08.028
 *
 * Created on 16 de novembro de 2022, 11:02
 */

#ifndef FILA_H
#define FILA_H

#include "lista.h"

typedef tLista tPilha; 

inline tPilha* inicia_fila(){
    return inicia_lista(); 
};

inline tPilha * encerra_fila(tPilha * p){
    return encerra_lista(p);
};

inline no * pop(tPilha * p){
    return remove_inicio(p);
};

/**
 * Insere nós no início da pilha;
 * @param ptlista cabeçalho da pilha.
 * @param p nó que aponta para a struct que será alocada.
 */
inline void push_pop(tPilha * BDpilha, no * BD){ 
    cout << "\n---------------- PILHA -----------------" << endl;
    cout << "\n Critérios:\n"
            " - Inserção em caso de direção hidráulico;\n"
            " - Remoção em caso de direção elétrico.\n";
    BDpilha->lista = BD;
    no * p = BDpilha->lista;
    while(p != NULL){
       if(p->v->direcao == "Hidráulica"){
           insere_inicio(BDpilha, p); 
        } else {
           pop(BDpilha);
        }
       p = p->prox;
    }
    
    //Impressão das placas em pilha.
    no * pont = BDpilha->lista;
    cout << "\n Tamanho atual da pilha: " << BDpilha->tam << endl;
    for(int j = 1; pont != NULL; j++){
        cout << " " << j << " - ";
        cout << pont->v->placa << endl;
        pont = pont->prox;
    }
    cout << "\n----------------------------------------" << endl;
};


#endif /* FILA_H */

