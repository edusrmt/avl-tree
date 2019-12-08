#ifndef AVL_TREE
#define AVL_TREE

#include<iostream>
#include<algorithm>

class No {
    public: 
    int chave;  
    int altura;  
    No *esquerda;  
    No *direita;

    No (int k) : chave{k}, altura{1}, esquerda{nullptr}, direita{nullptr} { }    
};
  
int getAltura (No *n) {  
    if (n == nullptr)  
        return 0;  

    return n->altura;
}  

No *rotacaoDireita (No *n) {  
    No *filho = n->esquerda;  
    No *t2 = filho->direita;  
  
    filho->direita = n;  
    n->esquerda = t2;  
   
    n->altura = std::max(getAltura(n->esquerda), getAltura(n->direita)) + 1;  
    filho->altura = std::max(getAltura(filho->esquerda), getAltura(filho->direita)) + 1;  
  
    return filho;  
}
  
No *rotacaoEsquerda (No *n) {  
    No *filho = n->direita;  
    No *t2 = filho->esquerda;  
  
    filho->esquerda = n;  
    n->direita = t2;  
   
    n->altura = std::max(getAltura(n->esquerda), getAltura(n->direita)) + 1;  
    filho->altura = std::max(getAltura(filho->esquerda), getAltura(filho->direita)) + 1;  
  
    return filho;  
}  
  
int getBalanco (No *n) {  
    if (n == nullptr)  
        return 0;  
    return getAltura(n->esquerda) - getAltura(n->direita);  
}

class ArvoreAVL {
    private:
    No *raiz;

    No* _inserir (No* n, int chave) {
        if (n == nullptr)  
            return(new No(chave));  
    
        if (chave < n->chave)  
            n->esquerda = _inserir(n->esquerda, chave);  
        else if (chave > n->chave)  
            n->direita = _inserir(n->direita, chave);  
        else
            return n;  
    
        n->altura = 1 + std::max(getAltura(n->esquerda), getAltura(n->direita));  
    
        int balanco = getBalanco(n);  
    
        if (balanco > 1 && chave < n->esquerda->chave)  
            return rotacaoDireita(n); 
        else if (balanco < -1 && chave > n->direita->chave)  
            return rotacaoEsquerda(n);       
        else if (balanco > 1 && chave > n->esquerda->chave) {  
            n->esquerda = rotacaoEsquerda(n->esquerda);  
            return rotacaoDireita(n);  
        } else if (balanco < -1 && chave < n->direita->chave) {  
            n->direita = rotacaoDireita(n->direita);  
            return rotacaoEsquerda(n);  
        }  

        return n;
    }

    void imprimirNivel (No *n, int nivel) {
        if (n == nullptr)
            return;

        if (nivel == 1)
            std::cout << n->chave << " ";
        else if (nivel >= 1) {
            imprimirNivel(n->esquerda, nivel - 1);
            imprimirNivel(n->direita, nivel - 1);
        }
    }

    public:
    ArvoreAVL () : raiz{nullptr} { }

    void inserir (int chave) {
        raiz = _inserir(raiz, chave);
    }

    void imprimir () {
        int altura = getAltura(raiz);
        
        for (int i = 0; i <= altura; i++) {
            imprimirNivel(raiz, i);
            std::cout << std::endl;
        }
    }    
};

#endif