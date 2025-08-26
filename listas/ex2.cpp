#include <iostream>

using namespace std;

struct noh {
  int matricula;
  string nome;
  int periodo;
  noh *proximo;
  noh *anterior;

  noh(int m, string n, int p) {
    this->matricula = m;
    this->nome = n;
    this->periodo = p;
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

  void inserirEmListaVazia(int m, string n, int p) {
    noh *novo = new noh(m, n, p);
    genesis = novo;
    apocalipse = novo;
    tamanho = 1;
  }

  void inserirNoInicioDaLista(int m, string n, int p) {
    if (this->vazia()) {
      inserirEmListaVazia(m, n, p);
    } else {
      noh *novo = new noh(m, n, p);
      novo->proximo = genesis;
      genesis->anterior = novo;
      genesis = novo;
      tamanho++;
    }
  }

  void inserirNoFimDaLista(int m, string n, int p) {
    if (this->vazia()) {
      inserirEmListaVazia(m, n, p);
    } else {
      noh *novo = new noh(m, n, p);
      apocalipse->proximo = novo;
      novo->anterior = apocalipse;
      apocalipse = novo;
      tamanho++;
    }
  }

  void imprimir() {
    if (this->vazia()){
      cout << "[]" << endl;
        return;
    }    
    noh *aux = genesis;
    cout << "[";
    while (aux->proximo != nullptr) {
      cout << aux->matricula << " - " << aux->nome << ", ";
      aux = aux->proximo;
    }
    cout << aux->matricula << " - " << aux->nome;
    cout << "]";
  }

  void inverter() {
    noh *atual = genesis;
    noh *aux = nullptr;
    while (atual) {
      aux = atual->proximo;
      atual->proximo = atual->anterior;
      atual->anterior = aux;
      atual = aux;
    }

    aux = genesis;
    genesis = apocalipse;
    apocalipse = aux;
  }

  bool vazia() { return this->genesis == nullptr; }
};

int main() {
  Lista l;
  int tamanho;
  cin >> tamanho;
  int matricula;
  int periodo;
  string nome;

  for (int i = 0; i < tamanho; i++) {
    cin >> matricula >> nome >> periodo;
    l.inserirNoFimDaLista(matricula, nome, periodo);
  }

  l.imprimir();
  l.inverter();
  cout << endl;
  l.imprimir();
}