/**
 * Discentes:
 *   Assucena Queren Lopes - RA: 2022.1.08.027
 *   Leandro Cesar de Souza Filho - RA: 2022.1.08.011
 *   Nicole Lima - RA: 2022.1.08.028
 * 
 *OBS: Em caso de erro "0 0 0" na escrita no final do arquivo ou de linha faltando,
 *decrementar ou comentar o decrementamento da variável tam na linha 338.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <valarray> 
#include <string>
#include <cmath>

#include "pilha.h"
#include "fila.h"
#include "lista.cpp"
#include "lista.h"

using namespace std;

template <typename T>
class Node
{
public:
    T value;
    Node *left;
    Node *right;
    int height;

    Node(T value)
    {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

template <typename T>
class AVL
{
public:
    Node<T> *root;

    AVL()
    {
        root = nullptr;
    }

    int height(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node<T> *insert(Node<T> *node, T value)
    {
        if (node == nullptr)
            return new Node<T>(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
       }

    Node<T> *deleteNode(Node<T> *node, T value)
    {
        if (node == nullptr)
            return node;

        if (value < node->value)
            node->left = deleteNode(node->left, value);

        else if (value > node->value)
            node->right = deleteNode(node->right, value);

        else
        {
            if ((node->left == nullptr) || (node->right == nullptr))
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(node->right);

                node->value = temp->value;

                node->right = deleteNode(node->right, temp->value);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            cout << node->value << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->value << " ";
        }
    }

};

template <typename T>
class BinaryTree
{
public:
    Node<T> *root;

    BinaryTree()
    {
        root = nullptr;
    }

    Node<T> *insert(Node<T> *node, T value)
    {        if (node == nullptr)
            return new Node<T>(value);

        if (value < node->value)
            node->left = insert(node->left, value);

        else if (value > node->value)
            node->right = insert(node->right, value);

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    Node<T> *deleteNode(Node<T> *node, T value)
    {
        if (node == nullptr)
            return node;

        if (value < node->value)
            node->left = deleteNode(node->left, value);

        else if (value > node->value)
            node->right = deleteNode(node->right, value);

        else
        {
            if ((node->left == nullptr) || (node->right == nullptr))
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(node->right);

                node->value = temp->value;

                node->right = deleteNode(node->right, temp->value);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            cout << node->value << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node<T> *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->value << " ";
        }
    }
};





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
    BD = inicia_lista();
    BD2 = inicia_lista();
    BDpilha = inicia_lista();
    BDfila = inicia_lista();
    
    leitura_arquivo(BD);

    AVL<int> avlTree;
    avlTree.root = avlTree.insert(avlTree.root, 100);
    avlTree.root = avlTree.insert(avlTree.root, 20);
    avlTree.root = avlTree.insert(avlTree.root, 380);
    avlTree.root = avlTree.insert(avlTree.root, 40);
    avlTree.root = avlTree.insert(avlTree.root, 50);
    avlTree.root = avlTree.insert(avlTree.root, 25);
    avlTree.inOrder(avlTree.root);

    cout << "ok?" << endl;
    int okay;
    cin >> okay;
    
    cout << "\n Bem-vindo ao Gerenciador de Busca de Veículos 2.0!" << endl;
        
        //Switch Case para o Menu que ocorre até o usuário digitar 0;
        do{
            cout << "\n Menu:\n  [1] - Inserção de novo veículo na lista\n "
                    " [2] - Busca de veículo por placa na lista\n "
                    " [3] - Pilha de veículos\n "
                    " [4] - Fila de veículos\n "
                    " [5] - Relatório da lista principal ordenada por placa\n "
                    " [6] - Relatório geral da lista principal\n "
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
