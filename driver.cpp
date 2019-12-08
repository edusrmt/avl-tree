#include <fstream>

#include "avl.hpp"

int main () {
    ArvoreAVL arvore;

    std::ifstream arquivo;
    arquivo.open("entrada.txt");

    int numero;
    while (arquivo >> numero) {
        arvore.inserir(numero);
    } 

    arquivo.close();     
    arvore.imprimir();  
      
    return 0;
}