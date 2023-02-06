/**
 * Discentes:
 *   Assucena Queren Lopes - RA: 2022.1.08.027
 *   Leandro Cesar de Souza Filho - RA: 2022.1.08.011
 *   Nicole Lima - RA: 2022.1.08.028
 * 
 * 
 *OBS: Em caso de erro "0 0 0" na escrita no final do arquivo ou de linha faltando,
 *decrementar ou comentar o decrementamento da variável tam na linha 338.
 *
 * Dromedário
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <valarray> 
#include <string>
#include <cmath>
//trabalinho fofinho 2
#include "pilha.h"
#include "fila.h"
#include "lista.cpp"
#include "lista.h"
//trabalhinho meigo 3
#include "arvore.h"
#include "binaria.cpp"
#include "avl.cpp"

using namespace std;

tLista * BD, *BD2, * BDpilha, *BDfila;

void fila(tLista *BDfila, no *BD){

    cout << "\n---------------- FILA -----------------" << endl;
    cout << "\n Critérios:\n"
            " - Inserção em caso de câmbio automático;\n"
            " - Remoção em caso de câmbio manual.\n";
    BDfila->lista = BD;
    no *p = BDfila->lista;

    while(p != NULL){
        if(p->v->cambio == "Automático"){
            insere_inicio(BDfila, p);
        } else {
            remove_fim(BDfila);
        }
        p = p->prox;
    }
    //Impressão das placas em fila.
    no * pont = BDfila->lista;
    cout << "\n Tamanho atual da fila: " << BDfila->tam << endl;
    for(int j = 1; pont != NULL; j++){
        cout << " " << j << " - ";
        cout << pont->v->placa << endl;
        pont = pont->prox;
    }
    cout << "\n----------------------------------------" << endl;
};

int main(int argc, char** argv){
    int opm;
    string placa;
    string jorge;
    BD = inicia_lista();
    BD2 = inicia_lista();
    BDpilha = inicia_lista();
    BDfila = inicia_lista();
    
    leitura_arquivo(BD);
    
    //cria a arv avl
    Arv* avl = nullptr;
    no * doberman = BD->lista;
    while (doberman != NULL)
    {
        //veiculo *nvcl = new veiculo;
        avl = inserirAVL(avl, doberman->v);
        doberman = doberman->prox;
    }

    //cria a arv binaria
    Arv* binaria = nullptr;
    doberman = BD->lista;
    while (doberman != NULL)
    {
        //veiculo *nvcl = new veiculo;
        binaria = inserir(binaria, doberman->v);
        doberman = doberman->prox;
    }

    //cria a arvore com filtro
    Arv* filtro = nullptr;
    doberman = BD->lista;
    cout << " \nFiltro de carros com cambio automatico e direção eletrica" << endl;
    while (doberman != NULL)
    {
        if(doberman->v->cambio == "Automático" && doberman->v->direcao == "Elétrica"){
          //veiculo *nvcl = new veiculo;
          filtro = inserirAVL(filtro, doberman->v);
        }
        doberman = doberman->prox;
    }
   
    cout << "\n Bem-vindo ao Gerenciador de Busca de Veículos 2.0!" << endl;
        
        //Switch Case para o Menu que ocorre até o usuário digitar 0;
        do{
            cout << "\n Menu:\n  [1] - Inserção de novo veículo na lista\n "
                    " [2] - Busca de veículo por placa na lista\n "
                    " [3] - Pilha de veículos\n "
                    " [4] - Fila de veículos\n "
                    " [5] - Relatório da lista principal ordenada por placa\n "
                    " [6] - Relatório geral da lista principal\n "
                    " [7] - Arvores\n "
                    " [0] - Sair\n Escolha uma opção: ";
            cin >> opm;          
            switch (opm){
            //Inserção
            case 1:
                insere_user(BD);             
                break;
            //Busca
            case 2:
                cout << "\n------------------------ BUSCA ------------------------" << endl;
                cout << " Informe a placa do veículo: ";
                cin >> placa;
                
                // Um nó "b" é declarado para receber a busca.
                no * b;
                // A busca é chamada para verificar se o veículo existe.
                b = busca(BD, placa);
                
                //Busca pela placa inserida e opção de remoção caso encontrada.
                if(b != NULL){
                    cout << " Veículo encontrado: ";
                    cout << b->v->marca << " "; 
                    cout << b->v->modelo << " ";
                    cout << b->v->tipo << " ";
                    cout << b->v->placa << " ";
                    cout << b->v->ano << endl;
                    
                    cout << "\n Fazer exclusão? (s/n): ";
                    string op;
                    cin >> op;
                    
                    // Transforma todos os caracteres da string placa em maíusculo.
                    for (auto & c: op) {
                        c = toupper(c);
                    }   
                    
                    //Repetição para caracteres inválidos na opção de remoção.
                    while(op != "S" && op != "N"){
                        cout << " Opção inválida! ";
                        cout << " Fazer exclusão? (s/n): ";
                        cin >> op;
                        
                        // Transforma todos os caracteres da string placa em maíusculo.
                        for (auto & c: op) {
                          c = toupper(c);
                        } 
                    }
                    
                    if(op == "S"){
                        remocao(BD, b);
                    }
                    else {
                        cout << "\n---------------------- REMOÇÃO -----------------------" << endl;
                        cout << " Veículo não removido!" << "\n------------------------------------------------------" << endl;
                    }
                }
                else {
                    cout << " Veículo não encontrado." << "\n------------------------------------------------------" << endl;
                }
                break;
            //Pilha
            case 3:
                push_pop(BDpilha, BD->lista);
                break;
            //Fila
            case 4:
                fila(BDfila, BD->lista);
                break;
            //Ordenação
            case 5:
                insere_ord(BD, BD2);
            break;
            //Relatório
            case 6:
                cout << "\n---------------------------------------- RELATÓRIO PRINCIPAL -------------------------------------------------" << endl;
                imprime(BD);
                cout <<"\n---------------------------------------------------------------------------------------------------" << endl;
                break;
            
            case 7:
                cout << " [0] - Para excluir um veiculo das arvores\n "
                        " [1] - Moste a Arvore Binaria em Pre-Ordem\n "
                        " [2] - Moste a Arvore AVL em Pre-Ordem\n "
                        " [3] - Moste a Arvore com filtro em Pre-Ordem\n " 
                        " [4] - Para adicionar um veiculo nas arvores\n "<< endl;
                int arv_ans;
                cin >> arv_ans;
                switch (arv_ans){
                    case 0:
                    cout << "placa do nó a ser excluido: ";
                    cin >> jorge;
                    excluirAVL(avl, jorge);
                    remover(binaria, jorge);
                    excluirAVL(filtro, jorge);
                    break;

                case 1:
                    preOrdem(binaria);
                break;
                    
                case 2:
                    preOrdem(avl);
                break;

                case 3:
                    preOrdem(filtro);                
                break;

                case 4:
                    no* ponti = insere_user(BD);
                    inserir(binaria,ponti->v);
                    inserirAVL(avl, ponti->v);
                    inserirAVL(filtro, ponti->v);
                break;

                }
            break;
            //Sair
            case 0:
                cout << "\n Bye-bye!";
                break;
            default:
                cout << " Opção inválida! \n";
                break;
            }
        } while(opm != 0);
        
    
    //Sobrescreve o arquivo-texto original com as novas alterações.
    ofstream myfile("BD_veiculos_2.txt");
    if(myfile.is_open()){
        no * ant = BD->lista;
        for(;ant != NULL; ant = ant->prox){
          myfile << ant->v->modelo << " ";
          myfile << ant->v->marca << " "; 
          myfile << ant->v->tipo << " ";
          myfile << ant->v->ano << " ";
          myfile << ant->v->km << " ";
          myfile << ant->v->potencia_do_motor << " ";
          myfile << ant->v->combustivel << " ";
          myfile << ant->v->cambio << " ";
          myfile << ant->v->direcao << " ";
          myfile << ant->v->cor << " ";
          myfile << ant->v->portas << " ";
          myfile << ant->v->placa << " ";
          myfile << ant->v->valor << " \n";
        }
        myfile.close();
    }
    else{
        cout << "Não foi possível criar o arquivo";
    }

    encerra_lista(BDpilha);
    encerra_lista(BDfila);
    encerra_lista(BD);

   
    return 0;
}