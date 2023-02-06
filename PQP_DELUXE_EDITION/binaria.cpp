#include "arvore.h"
#include "lista.h"

using namespace std;

Arv* inserir(Arv* raiz, veiculo *veiculo) {
  if (raiz == nullptr) {
    raiz = new Arv;
    raiz->carro = veiculo;
    raiz->esq = raiz->dir = nullptr;
  } else if (veiculo->placa < raiz->carro->placa) {
    raiz->esq = inserir(raiz->esq, veiculo);
  } else {
    raiz->dir = inserir(raiz->dir, veiculo);
  }
  return raiz;
}

Arv* procurarMenor(Arv* raiz) {
  while (raiz->esq != nullptr) {
    raiz = raiz->esq;
  }
  return raiz;
}

Arv* remover(Arv* raiz, string placa) {
  if (raiz == NULL) {
    return NULL;
  } else if (placa < raiz->carro->placa) {
    raiz->esq = remover(raiz->esq, placa);
  } else if (placa > raiz->carro->placa) {
    raiz->dir = remover(raiz->dir, placa);
  } else {
    if (raiz->esq == NULL && raiz->dir == NULL) {
      delete raiz;
      return NULL;
    } else if (raiz->esq == NULL) {
      Arv* temp = raiz->dir;
      delete raiz;
      return temp;
    } else if (raiz->dir == NULL) {
      Arv* temp = raiz->esq;
      delete raiz;
      return temp;
    } else {
      Arv* temp = procurarMenor(raiz->dir);
      raiz->carro = temp->carro;
      raiz->dir = remover(raiz->dir, temp->carro->placa);
      return raiz;
    }
  }
  return raiz;
}


void emOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  emOrdem(raiz->esq);
  cout << raiz->carro->placa << " ";
  emOrdem(raiz->dir);
}

void preOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  cout << raiz->carro->placa << " ";
  preOrdem(raiz->esq);
  preOrdem(raiz->dir);
}

void posOrdem(Arv* raiz) {
  if (raiz == nullptr) {
    return;
  }
  posOrdem(raiz->esq);
  posOrdem(raiz->dir);
  cout << raiz->carro->placa << " ";
}