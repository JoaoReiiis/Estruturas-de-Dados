#include <iostream>

using namespace std;

struct noh {
  char letra;
  noh *proximo;

  noh(char l) {
    this->letra = l;
    proximo = nullptr;
  }
};

class Lista {
  noh *genesis;
  noh *apocalipse;
  int tamanho;

public:
  Lista() {
    genesis = nullptr;
    apocalipse = nullptr;
    tamanho = 0;
  }

  void inserirEmListaVazia(char l) {
    noh *novo = new noh(l);
    genesis = novo;
    apocalipse = novo;
    tamanho = 1;
  }

  void inserirNoFimDaLista(char l) {
    if (this->vazia()) {
      inserirEmListaVazia(l);
    } else {
      noh *novo = new noh(l);
      apocalipse->proximo = novo;
      apocalipse = novo;
      tamanho++;
    }
  }

  char removeNoFim() {
    if (this->vazia())
      throw exception();

    noh *aux = genesis;
    noh *anterior = nullptr;

    while (aux->proximo != nullptr) {
      anterior = aux;
      aux = aux->proximo;
    }

    char valor = aux->letra;

    if (anterior) {
      anterior->proximo = nullptr;
      apocalipse = anterior;
    } else {
      genesis = nullptr;
      apocalipse = nullptr;
    }

    delete aux;
    tamanho--;
    return valor;
  }
  
  string palindromo() {
    int n = tamanho;
    if(n < 2) return "sim";

    noh *aux = genesis;

    for(int i = 0; i < n/2; i++){
        char fim = this->removeNoFim();
        //cout << "letra(" << i << "): " << aux->letra << " fim: " << fim << endl;
        if(aux->letra != fim) return "nao";
        aux = aux->proximo;
    }
    return "sim";
  }

  bool vazia() { return genesis == nullptr; }
};

int main() {
  char letra;
  Lista l;
  while ((cin >> letra) && (letra != '#')) {
    l.inserirNoFimDaLista(letra);
  }
  cout << l.palindromo() << endl;
  return 0;
}