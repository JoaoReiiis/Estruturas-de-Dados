#include <iostream>

using namespace std;

struct noh {
  int numero;
  noh *proximo;
  noh *anterior;

  noh(int n) {
    this->numero = n;
    proximo = nullptr;
    anterior = nullptr;
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

  void inserirEmListaVazia(int n) {
    noh *novo = new noh(n);
    genesis = novo;
    apocalipse = novo;
    tamanho = 1;
  }

  void inserirNoFimDaLista(int n) {
    if (this->vazia()) {
      inserirEmListaVazia(n);
    } else {
      noh *novo = new noh(n);
      apocalipse->proximo = novo;
      novo->anterior = apocalipse;
      apocalipse = novo;
      tamanho++;
    }
  }


  bool vazia() { return this->genesis == nullptr; }
};

int main(){
    Lista l1;
    Lista l2;
    Lista l3;
    return 0;
}