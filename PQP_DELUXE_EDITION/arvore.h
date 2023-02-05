#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <valarray> 
#include <cmath>


struct Arv {
  std::string valor;
  int altura;
  Arv* esq;
  Arv* dir;
};


#endif