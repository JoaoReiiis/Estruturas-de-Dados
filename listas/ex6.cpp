#include <iostream>

using namespace std;

struct noh {
  int numero;
  noh *proximo;

  noh(int n) {
    this->numero = n;
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
      apocalipse = novo;
      tamanho++;
    }
  }

  void removeNoInicio() {
    noh *aux = genesis;
    genesis = aux->proximo;
    delete aux;
    tamanho--;
    if (this->vazia())
      genesis = nullptr;
  }

  void removeNoFim() {
    noh *aux = genesis;
    noh *anterior = nullptr;

    while (aux->proximo != nullptr) {
      anterior = aux;
      aux = aux->proximo;
    }

    if (anterior == nullptr) {
      genesis = nullptr;
      apocalipse = nullptr;
    } else {
      anterior->proximo = nullptr;
      apocalipse = anterior;
    }

    delete aux;
    tamanho--;
  }

  void removeEspecifico(int valor) {
    noh *aux = genesis;
    noh *anterior;
    while (aux != nullptr && aux->numero != valor) {
      anterior = aux;
      aux = aux->proximo;
    }

    if (aux != nullptr) {
      if (aux == genesis) {
        removeNoInicio();
      } else if (aux == apocalipse) {
        removeNoFim();
      } else {
        anterior->proximo = aux->proximo;
        tamanho--;
        delete aux;
      }
    }
  }

  void imprime() {
    noh *aux = genesis;

    while (aux != nullptr) {
      cout << aux->numero << " ";
      aux = aux->proximo;
    }
    cout << endl;
  }

  bool vazia() { return genesis == nullptr; }
};

int main() {
  int numero;
  Lista l1;
  Lista l2;
  Lista l3;
  int *arr = new int[3];

  for (int i = 0; i < 5; i++) {
    cin >> numero;
    l1.inserirNoFimDaLista(numero);
    l3.inserirNoFimDaLista(numero);
  }

  for (int i = 0; i < 5; i++) {
    cin >> numero;
    l2.inserirNoFimDaLista(numero);
    l3.inserirNoFimDaLista(numero);
  }

  for (int i = 0; i < 3; i++) {
    cin >> numero;
    arr[i] = numero;
  }

  l3.imprime();
  l1.imprime();
  l2.imprime();

  l3.removeEspecifico(arr[0]);
  l3.removeEspecifico(arr[1]);
  l3.removeEspecifico(arr[2]);

  l3.imprime();

  delete[] arr;
  return 0;
}