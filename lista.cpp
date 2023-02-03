/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <valarray> 

#include "lista.h"
#include "pilha.h"
#include "fila.h"

using namespace std;

/**
 * Realiza a alocacao do espaco para que a lista possa comecar.
 * a receber nos.
 * @return a lista vazia.
 */
tLista* inicia_lista() {
    tLista* tmp = new(tLista);
    tmp->tam = 0;
    tmp->lista = NULL;

//    cout << "-A lista foi iniciada."<<endl;
    return tmp;
}

/**
 * Desaloca o espaco previamente alocado para a lista encadeada.
 * @param ptlista ponteiro para a lista.
 * @return NULL para atualizar o ponteiro da lista.
 */
tLista * encerra_lista(tLista * ptlista) {
    no * ant = ptlista->lista;
    no * pont = ptlista->lista;

    while(ant != NULL){
        pont = ant->prox;
        delete(ant);
        ant = pont;
    }
    delete(ptlista);
//    cout << "\n-A fila foi removida."<<endl;

    return NULL;
}

/**
 * Lê o arquivo texto e aloca memória para a nova struct que receberá
 * as informações dos veículos.
 * @param ptlista ponteiro para a lista.
 */

void leitura_arquivo(tLista *ptlista) {
  ifstream myfile ("BD_veiculos_2.txt");
  if(myfile.is_open()){
    while( !myfile.eof()){
        no * ant;
        no *atual = new(no);
        atual->v = new(veiculo);
        myfile >> atual->v->modelo;
        myfile >> atual->v->marca;
        myfile >> atual->v->tipo;
        myfile >> atual->v->ano;
        myfile >> atual->v->km;
        myfile >> atual->v->potencia_do_motor;
        myfile >> atual->v->combustivel;
        myfile >> atual->v->cambio;
        myfile >> atual->v->direcao;
        myfile >> atual->v->cor;
        myfile >> atual->v->portas;
        myfile >> atual->v->placa;
        myfile >> atual->v->valor;
        if(ptlista->tam == 0){
            ptlista->lista = atual;
            ant = atual;
            ptlista->tam++;
        }else{
            ant->prox = atual;
            ant = ant->prox;
            ptlista->tam++;
        }    
    }
    myfile.close();
    }else{
      cout << "Arquivo não encontrado";
    }
}

/**
 * Insere nós no início da lista;
 * @param ptlista cabeçalho da lista;
 * @param p nó que aponta para a struct que será alocada.
 */
void insere_inicio(tLista * ptlista, no * p){
    no * novo = new(no);
    novo->v = p->v;
    novo->prox = ptlista->lista;
    ptlista->lista = novo;
    ptlista->tam++;
}

/**
 * Insreção do nó no fim da lista passada;
 * @param nó a ser inserido.
 */
void insere_fim(tLista * ptlista, no * p) {
        if (ptlista->tam == 0) {
            insere_inicio(ptlista, p);
        } else {
            no* novo = ptlista->lista;
            while (p->prox != NULL)
                p = p->prox;
            novo->prox = new(no);
            novo->prox->v = p->v;
            novo->prox->prox = NULL;
            ptlista->tam++;
        }
}

/**
 * Busca um nó na lista pela placa;
 * @param ptlista cabeçalho da lista;
 * @param placa a ser buscada;
 * @return nó em caso de nó existente, NULL caso contrário.
 */
no * busca(tLista * ptlista, string placa){
    // Transforma todos os caracteres da string placa em maíusculo.
    for (auto & c: placa) {
        c = toupper(c);
    }
    no * busca = ptlista->lista;
    while(busca != NULL) {
        if(placa == busca->v->placa){
            return busca;
        }
        else{
            busca = busca->prox;
        }
    }
    return NULL;

}

/**
 * Inserção na lista pelo usuário.
 * @param ptlista: cabeçalho da lista.
 * @return NULL caso veículo já incluso, o nó inserido caso contrário. 
 */
no * insere_user(tLista * ptlista){
    cout << "\n--------------------- INSERÇÃO ---------------------\n" << endl;
    cout << " Informe a placa do veículo: ";
    string placa;
    cin >> placa;
    
    // Transforma todos os caracteres da string placa em maíusculo.
    for (auto & c: placa) {
        c = toupper(c);
    }
    
    // Um nó "b" é declarado para receber a busca.
    no * b;
    
    // A busca é chamada para verificar se o veículo já está incluso.
    b = busca(ptlista, placa);
    
    // Se o veículo já existe, a inclusão não é feita.
    if(busca(ptlista, placa) != NULL){
        cout << " Veiculo já existe: ";
        cout << b->v->modelo << " ";
        cout << b->v->modelo << " ";
        cout << b->v->tipo << " ";
        cout << b->v->placa << " ";
        cout << b->v->ano << " ";
        cout << endl <<" Veículo não inserido." << "\n----------------------------------------" << endl;
        return NULL;
    }
    else{
        
        // Uma nova struct é alocada para receber as informações
        // do veículo que será inserido na lista.
        veiculo * novo = new(veiculo);
        
        // A placa utilizada como parâmetro de busca é inserida na lista.
        novo->placa = placa;
        
        // As demais informações do veículo serão inseridas pelo usuário.
        cout << " Informe o modelo: ";
        cin >> novo->modelo;
        
        // Transforma todos os caracteres da string modelo em maíusculo.
        for (auto & c: novo->modelo) {
            c = toupper(c);
        }
        
        cout << " Informe a marca: ";
        cin >> novo->marca;
        
        // Transforma todos os caracteres da string marca em maíusculo.
        for (auto & c: novo->marca) {
            c = toupper(c);
        }
        
        cout << " Informe o tipo: ";
        cin >> novo->tipo;
        cout << " Informe o ano: ";
        cin >> novo->ano;
        cout << " Informe o km: ";
        cin >> novo->km;
        cout << " Informe a potência do motor: ";
        cin >> novo->potencia_do_motor;
        cout << " Informe o combustível: ";
        cin >> novo->combustivel;
        
         // Opções para otimizar as funções de fila.
        cout << " Informe o câmbio ([1] Manual / [2] Automático): ";
        int opc;
        cin >> opc;
        while(opc != 1 && opc != 2){
            cout << " Opção inválida! \n";
            cout << " Informe o câmbio ([1] Manual / [2] Automático): ";
            cin >> opc;
        }
        // Switch Case para definir qual das opções o câmbio vai receber.
        switch (opc){
            case 1:
                novo->cambio = "Manual";
            break;
            case 2:
                novo->cambio = "Automático";
            break;
                
        }
       
        
        // Opções para otimizar as funções de pilha.
        cout << " Informe a direção ([1] Hidráulica / [2] Elétrica): ";
        int opd;
        cin >> opd;
        while(opd != 1 && opd != 2){
            cout << " Opção inválida! \n";
            cout << " Informe a direção ([1] Hidráulica / [2] Elétrica): ";
            cin >> opd;
        }
        // Switch Case para definir qual das opções a direção vai receber.
        switch (opd){
            case 1:
                novo->direcao = "Hidráulica";
            break;
            case 2:
                novo->direcao = "Elétrica";
            break;
                
        }
        
        cout << " Informe a cor: ";
        cin >> novo->cor;
        cout << " Informe as portas: ";
        cin >> novo->portas;
        cout << " Informe o valor: ";
        cin >> novo->valor;
        cout << endl;
        
        // Ligação entre os nós da lista ao nó inserirdo
        no * ant = ptlista->lista->prox;
        no * pont;
        
        while(ant->prox != NULL){
            ant = ant->prox;
        }
        
        pont = new (no);
        pont->v = novo;
        
        ant->prox = pont;
        pont->prox = NULL;
        ptlista->tam++; 
        
        cout << "----------------------------------------------------" << endl;

        return pont;  
    }
}

/**
 * Remoção pelo início da lista passada.
 * @param ptlista cabeçalho da lista;
 * @return ptr nó removido, NULL caso contrário (lista vazia).
 */
no * remove_inicio(tLista * ptlista){
    if (ptlista->tam == 0){
        return NULL;
    }
    no *ptr = ptlista->lista;
    if (ptlista->tam == 1){
        ptlista->lista = NULL;
        ptlista->tam--;
        return ptr;
    }
    ptlista->lista = ptr->prox;
    ptlista->tam--;
    return ptr;
}

/**
 * Remoção de um nó da lista;
 * @param ptlista cabeçalho da lista;
 * @param b nó que será removido.
 */
void remocao(tLista *ptlista, no * b){
    cout << "\n---------------------- REMOÇÃO -----------------------" << endl;
    no * ant = ptlista->lista;
    while(ant->prox != b){
        ant = ant->prox;
    }
    ant->prox = b->prox;
    
    //Desalocando a memória do nó;
    delete(b->v);
    delete(b);
    ptlista->tam--;
    cout << " Veículo removido!\n------------------------------------------------------" << endl;
}

/**
 * Imprime a lista passada.
 * @param d struct a ser impressa.
 * @param tam tamanho da struct a ser impressa.
 */
void imprime(tLista * ptlista){
    if(ptlista->lista == NULL){
        cout << "\n Não foi possível imprimir, não há veículos.\n" << endl;
    } else {
        no * pont = ptlista->lista->prox;
       cout << "\n Tamanho atual: " << ptlista->tam << endl;
        for(int j = 1; pont != NULL; j++){
            cout << " " << j << " - ";
            cout << pont->v->modelo << " ";
            cout << pont->v->marca << " ";
            cout << pont->v->tipo << " ";
            cout << pont->v->ano << " ";
            cout << pont->v->km << " ";
            cout << pont->v->potencia_do_motor << " ";
            cout << pont->v->combustivel << " ";
            cout << pont->v->cambio << " ";
            cout << pont->v->direcao << " ";
            cout << pont->v->cor << " ";
            cout << pont->v->portas << " ";
            cout << pont->v->placa << " ";
            cout << pont->v->valor << " " << endl;
            pont = pont->prox;
        }
    }
    
}

/**
 * Inserção ordenada dos nós da lista principal pela placa numa nova lista;
 * @param cima cabeçalho da lista principal;
 * @param fim cabeçalho duplicado que receberá a lista ordenada.
 */
void insere_ord(tLista * cima, tLista * fim){
    cout << "\n---------------------------------------- RELATÓRIO ORDENAÇÃO -------------------------------------------------" << endl;

    no * ptr;
    no *ant;
    no * aux = cima->lista;
    no * aux2;
    
    fim->lista = new(no);
    fim->tam++;
    fim->lista->prox = NULL;
    fim->lista->v = aux->v;
    
    ant = fim->lista;
    ptr = ant->prox;
   
    for(int i = 0; i < cima->tam ; i++){
      while(ptr != NULL && aux->v->placa > ptr->v->placa ){
        ant = ptr;
        ptr = ptr->prox;
      }
      aux2 = new(no);
      aux2->v = aux->v;
      aux2->prox = ptr;
      ant -> prox = aux2;
      aux = aux->prox;
      ant = fim->lista;
      ptr = ant->prox;
      fim->tam++;
    }
    fim->lista = fim->lista->prox;  
    ptr = fim->lista;
    fim->tam--;
    
    imprime(fim);
    fim->tam = 0;
    delete(ptr);
    cout <<"\n---------------------------------------------------------------------------------------------------" << endl;

}

/**
 * Remove o último nó da lista passada, se este existir;
 * @param ptlista cabeçalho da lista;
 * @return NULL em caso de lista vazia, o nó removido caso contrário.
 */
no *remove_fim(tLista *ptlista) {
  no *ant = ptlista->lista;
  if (ptlista->tam == 0) {
    return ant;
  }
  if (ptlista->tam == 1) {
    return remove_inicio(ptlista);
  }

  for (int i = 2; i <= ptlista->tam - 1; i++) {
    ant = ant->prox;
  }
  no * ptr = ant->prox;
  ant->prox = NULL;
  ptlista->tam--;
  return ptr;
}
