#include <iostream>
#include <fstream>
#include <valarray>

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
