#include <iostream>

using namespace std;

struct noh {
  int valor;
  noh *proximo;
  noh *anterior;

  noh(int v) {
    this->valor = v;
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

  void inserirEmListaVazia(int valor) {
    noh *novo = new noh(valor);
    genesis = novo;
    apocalipse = novo;
    tamanho = 1;
  }

  void inserirNoInicioDaLista(int valor) {
    if (this->vazia()) {
      inserirEmListaVazia(valor);
    } else {
      noh *novo = new noh(valor);
      novo->proximo = genesis;
      genesis->anterior = novo;
      genesis = novo;
      tamanho++;
    }
  }

  void inserirNoFimDaLista(int valor) {
    if (this->vazia()) {
      inserirEmListaVazia(valor);
    } else {
      noh *novo = new noh(valor);
      apocalipse->proximo = novo;
      novo->anterior = apocalipse;
      apocalipse = novo;
      tamanho++;
    }
  }

  void imprimir() {
    noh *aux = genesis;

    while (aux != nullptr) {
      cout << aux->valor << " ";
      aux = aux->proximo;
    }
  }

  int removeNoInicio() {
    noh *aux = genesis;
    int valor = aux->valor;
    genesis = aux->proximo;
    delete aux;
    tamanho--;
    return valor;
  }

  int removeNoFim() {
    noh *aux = apocalipse;
    int valor = aux->valor;
    apocalipse = aux->anterior;
    apocalipse->proximo = nullptr;
    delete aux;
    tamanho--;
    return valor;
  }

  Lista split(int n) {
    if (n >= tamanho)
      return *this;

    Lista laux;

    for (int i = tamanho - 1; i > n; i--) {
      laux.inserirNoInicioDaLista(this->removeNoFim());
    }
    return laux;
  }

  bool vazia() { return genesis == nullptr; }

  void teste() { cout << genesis->valor << endl << apocalipse->valor; }
};

int main() {
  Lista l;
  int t = 0;
  cin >> t;
  int numero;
  for (int i = 0; i < t; i++) {
    cin >> numero;
    l.inserirNoFimDaLista(numero);
  }

  int n = 0;
  cin >> n;
  if (n > t-1) {
    l.imprimir();
    cout << endl << -1;
  } else if (n == t-1) {
    l.imprimir();
    cout << endl;
  } else {
    Lista lsplit = l.split(n);

    l.imprimir();
    cout << endl;
    lsplit.imprimir();
  }
  return 0;
}