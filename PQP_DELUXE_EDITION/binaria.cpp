#include "arvore.h"
#include "lista.h"

using namespace std;

Arv* inserir(Arv* raiz, std::string valor) {
  if (raiz == nullptr) {
    raiz = new Arv;
    raiz->valor = valor;
    raiz->esq = raiz->dir = nullptr;
  } else if (valor < raiz->valor) {
    raiz->esq = inserir(raiz->esq, valor);
  } else {
    raiz->dir = inserir(raiz->dir, valor);
  }
  return raiz;
}

Arv* procurarMenor(Arv* raiz) {
  while (raiz->esq != nullptr) {
    raiz = raiz->esq;
  }
  return raiz;
}

Arv* remover(Arv* raiz, string valor) {
  if (raiz == nullptr) {
    return raiz;
  } else if (valor < raiz->valor) {
    raiz->esq = remover(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = remover(raiz->dir, valor);
  } else {
    if (raiz->esq == nullptr && raiz->dir == nullptr) {
      delete raiz;
      raiz = nullptr;
    } else if (raiz->esq == nullptr) {
      Arv* temp = raiz;
      raiz = raiz->dir;
      delete temp;
    } else if (raiz->dir == nullptr) {
      Arv* temp = raiz;
      raiz = raiz->esq;
      delete temp;
    } else {
      Arv* temp = procurarMenor(raiz->dir);
      raiz->valor = temp->valor;
      raiz->dir = remover(raiz->dir, temp->valor);
    }
  }
  return raiz;
}

void emOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  emOrdem(raiz->esq);
  cout << raiz->valor << " ";
  emOrdem(raiz->dir);
}

void preOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  cout << raiz->valor << " ";
  preOrdem(raiz->esq);
  preOrdem(raiz->dir);
}

void posOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  posOrdem(raiz->esq);
  posOrdem(raiz->dir);
  cout << raiz->valor << " ";
}

Arv* geraArvBinaria(Arv* raiz, tLista *BD){
    no * doberman = BD->lista;
    while (doberman != NULL)
    {
        raiz = inserir(raiz, doberman->v->placa);
        doberman = doberman->prox;
    }
    preOrdem(raiz);
    return 0;
}