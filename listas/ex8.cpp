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

    while (aux) {
      cout << aux->valor << " ";
      aux = aux->proximo;
    }
  }

  void imprimirReverso(){
    noh *aux = apocalipse;

    while(aux){
      cout << aux->valor << " ";
      aux = aux->anterior;
    }
  }

  void removeElementos(Lista &l2) {
    noh *aux = genesis;
    while (aux) {
      noh *prox = aux->proximo; 

      for (noh *j = l2.genesis; j; j = j->proximo) {
        if (j->valor == aux->valor) {
          if (aux->anterior)
            aux->anterior->proximo = aux->proximo;
          else
            genesis = aux->proximo;

          if (aux->proximo)
            aux->proximo->anterior = aux->anterior;
          else
            apocalipse = aux->anterior;

          delete aux;
          tamanho--;
        }
      }
      aux = prox;
    }

    if(this->vazia())
      cout << -1;
  }

  bool vazia() { return genesis == nullptr; }

  void teste() { cout << genesis->valor << endl << apocalipse->valor; }
};

int main() {
  Lista l1;
  Lista l2;
  int numero;
  int n = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> numero;
    l1.inserirNoFimDaLista(numero);
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> numero;
    l2.inserirNoFimDaLista(numero);
  }
  l1.removeElementos(l2);
  l1.imprimir();
  cout << endl;
  l1.imprimirReverso();
  return 0;
}