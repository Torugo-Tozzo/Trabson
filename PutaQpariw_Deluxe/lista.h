/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   lista.h
 * Author: 2022.1.08.028
 *
 * Created on 8 de novembro de 2022, 19:34
 */

#ifndef LISTA_H
#define LISTA_H

using namespace std;

//dados do veículo
typedef struct veiculo {
    string modelo;
    string marca;
    string tipo;
    string ano;
    string km;
    string potencia_do_motor;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    string portas;
    string placa; 
    float valor;
}veiculo;

//nó da lista
typedef struct no_ {
	veiculo * v;  
	struct no_ * prox;  // ponteiro para o próximo nó da lista encadeada
} no;


//cabeçalho
typedef struct {
	int tam;            //critério de busca da ordenação
	struct no_ * lista; // ponteiro para o próximo nó da lista encadeada
} tLista;

tLista* inicia_lista();
tLista * encerra_lista(tLista * ptlista);
void leitura_arquivo(tLista * ptlista);
void imprime(tLista * ptlista);
void insere_inicio(tLista * ptlista, no * p);
void remocao(tLista *ptlista, no * b);
no * remove_inicio(tLista * ptlista);
no * remove_fim(tLista * ptlista);
void insere_fim(tLista * ptlista, no * p);
no * busca(tLista * ptlista, string placa);
no * insere_user(tLista * ptlista);
void insere_ord(tLista * cima, tLista * fim);

#endif /* LISTA_H */

