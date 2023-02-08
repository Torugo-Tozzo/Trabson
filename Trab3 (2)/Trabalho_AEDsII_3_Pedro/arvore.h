#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <valarray> 
#include <cmath>
#include "lista.h"

struct Arv {
  veiculo* carro;
  int altura;
  Arv* esq;
  Arv* dir;
};

#endif