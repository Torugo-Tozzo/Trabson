#include "arvore.h"
#include "lista.h"

int altura(Arv* raiz) {
  if (raiz == nullptr) {
    return 0;
  }
  return raiz->altura;
}

int fatorBalanco(Arv* raiz) {
  if (raiz == nullptr) {
    return 0;
  }
  return altura(raiz->esq) - altura(raiz->dir);
}

Arv* novoNo(veiculo* carrim) {
Arv* novoNo = new Arv;
novoNo->carro = carrim;
novoNo->altura = 1;
novoNo->esq = novoNo->dir = nullptr;
return novoNo;
}

Arv* rotacaoEsq(Arv* raiz) {
  Arv* x = raiz->dir;
  Arv* y = x->esq;
  
  x->esq = raiz;
  raiz->dir = y;
  
  raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
  x->altura = max(altura(x->esq), altura(x->dir)) + 1;
  
  return x;
}

Arv* rotacaoDir(Arv* raiz) {
  Arv* x = raiz->esq;
  Arv* y = x->dir;
  
  x->dir = raiz;
  raiz->esq = y;
  
  raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
  x->altura = max(altura(x->esq), altura(x->dir)) + 1;
  
  return x;
}

Arv* rotacaoEsqDir(Arv* raiz) {
  raiz->esq = rotacaoEsq(raiz->esq);
  return rotacaoDir(raiz);
}

Arv* rotacaoDirEsq(Arv* raiz) {
  raiz->dir = rotacaoDir(raiz->dir);
  return rotacaoEsq(raiz);
}

Arv* inserirAVL(Arv* raiz, veiculo* car) {
if (raiz == NULL) { // Se a raiz estiver vazia, cria um novo nó
Arv* novo = new Arv();
novo->carro = car;
novo->altura = 1;
novo->esq = NULL;
novo->dir = NULL;
return novo;
} else if (car->placa < raiz->carro->placa) { // Se o carro for menor, insere à esquerda
raiz->esq = inserirAVL(raiz->esq, car);
} else if (car->placa > raiz->carro->placa) { // Se o carro for maior, insere à direita
raiz->dir = inserirAVL(raiz->dir, car);
} else { // Se o carro já existir, retorna a raiz sem modificações
return raiz;
}

// Atualiza a altura da raiz
raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

// Verifica se a raiz está desequilibrada e corrige se necessário
int fatorBalanceamento = fatorBalanco(raiz);
if (fatorBalanceamento > 1 && car->placa < raiz->esq->carro->placa) {
return rotacaoDir(raiz);
}
if (fatorBalanceamento < -1 && car->placa > raiz->dir->carro->placa) {
return rotacaoEsq(raiz);
}
if (fatorBalanceamento > 1 && car->placa > raiz->esq->carro->placa) {
raiz->esq = rotacaoEsq(raiz->esq);
return rotacaoDir(raiz);
}
if (fatorBalanceamento < -1 && car->placa < raiz->dir->carro->placa) {
raiz->dir = rotacaoDir(raiz->dir);
return rotacaoEsq(raiz);
}

// Retorna a raiz
return raiz;
}

Arv* minimo(Arv* raiz) {
  while (raiz->esq) {
    raiz = raiz->esq;
  }
  return raiz;
}

Arv* excluirAVL(Arv* raiz, string valor) {
  if (!raiz) {
    return nullptr;
  }
  
  if (valor < raiz->carro->placa) {
    raiz->esq = excluirAVL(raiz->esq, valor);
  } else if (valor > raiz->carro->placa) {
    raiz->dir = excluirAVL(raiz->dir, valor);
  } else {
    if (!raiz->esq || !raiz->dir) {
      Arv* filho = raiz->esq ? raiz->esq : raiz->dir;
      if (!filho) {
        filho = raiz;
        raiz = nullptr;
      } else {
        *raiz = *filho;
      }
      delete filho;
    } else {
      Arv* sucessor = minimo(raiz->dir);
      raiz->carro->placa = sucessor->carro->placa;
      raiz->dir = excluirAVL(raiz->dir, sucessor->carro->placa);
    }
  }
  
  if (!raiz) {
    return nullptr;
  }
  
  raiz->altura = std::max(altura(raiz->esq), altura(raiz->dir)) + 1;
  
  int fb = fatorBalanco(raiz);
  
  if (fb > 1 && fatorBalanco(raiz->esq) >= 0) {
    return rotacaoDir(raiz);
  }
  
  if (fb > 1 && fatorBalanco(raiz->esq) < 0) {
    return rotacaoEsqDir(raiz);
  }
  
  if (fb < -1 && fatorBalanco(raiz->dir) <= 0) {
    return rotacaoEsq(raiz);
  }
  
  if (fb < -1 && fatorBalanco(raiz->dir) > 0) {
    return rotacaoDirEsq(raiz);
  }
  
  return raiz;
}