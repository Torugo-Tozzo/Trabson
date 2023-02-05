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

Arv* novoNo(string valor) {
  Arv* novo = new Arv();
  novo->valor = valor;
  novo->altura = 1;
  novo->esq = nullptr;
  novo->dir = nullptr;
  return novo;
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

Arv* inserirAVL(Arv* raiz, string valor) {
  if (!raiz) {
    Arv* novo = new Arv();
    novo->valor = valor;
    novo->altura = 1;
    novo->esq = novo->dir = nullptr;
    return novo;
  }
  
  if (valor < raiz->valor) {
    raiz->esq = inserirAVL(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = inserirAVL(raiz->dir, valor);
  } else {
    return raiz;
  }
  
  raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
  
  int fb = fatorBalanco(raiz);
  
  if (fb > 1 && valor < raiz->esq->valor) {
    return rotacaoDir(raiz);
  }
  
  if (fb < -1 && valor > raiz->dir->valor) {
    return rotacaoEsq(raiz);
  }
  
  if (fb > 1 && valor > raiz->esq->valor) {
    return rotacaoEsqDir(raiz);
  }
  
  if (fb < -1 && valor < raiz->dir->valor) {
    return rotacaoDirEsq(raiz);
  }
  
  return raiz;
}

Arv* minimo(Arv* raiz) {
  while (raiz->esq) {
    raiz = raiz->esq;
  }
  return raiz;
}

Arv* excluirAVL(Arv* raiz, std::string valor) {
  if (!raiz) {
    return nullptr;
  }
  
  if (valor < raiz->valor) {
    raiz->esq = excluirAVL(raiz->esq, valor);
  } else if (valor > raiz->valor) {
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
      raiz->valor = sucessor->valor;
      raiz->dir = excluirAVL(raiz->dir, sucessor->valor);
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

Arv* geraArvAVL(Arv* raiz, tLista *BD){
    no * doberman = BD->lista;
    while (doberman != NULL)
    {
        raiz = inserirAVL(raiz, doberman->v->placa);
        doberman = doberman->prox;
    }
   preOrdem(raiz);
}

Arv* geraArvFiltro(Arv* raiz, tLista *BD){
    no * doberman = BD->lista;
    cout << " \nFiltro de carros com cambio automatico e direção eletrica" << endl;
    while (doberman != NULL)
    {
        if(doberman->v->cambio == "Automático" && doberman->v->direcao == "Elétrica"){
          raiz = inserirAVL(raiz, doberman->v->placa);
        }
        doberman = doberman->prox;
    }
    preOrdem(raiz);
    return 0;
}