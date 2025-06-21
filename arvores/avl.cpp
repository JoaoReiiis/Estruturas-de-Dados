#include <iostream>
using namespace std;

struct Noh {
  int valor;
  int altura;
  Noh *esquerdo;
  Noh *direito;

  Noh(int v) : valor(v), altura(1), esquerdo(nullptr), direito(nullptr) {}
};

class AVL {
private:
  Noh *raiz;

  int altura(Noh *n) { return n ? n->altura : 0; }

  void atualizaAltura(Noh *n) {
    n->altura = 1 + max(altura(n->esquerdo), altura(n->direito));
  }

  int fatorBalanceamento(Noh *n) {
    return n ? altura(n->esquerdo) - altura(n->direito) : 0;
  }

  Noh *rotacaoDireita(Noh *y) {
    Noh *x = y->esquerdo;
    Noh *T2 = x->direito;

    x->direito = y;
    y->esquerdo = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
  }

  Noh *rotacaoEsquerda(Noh *x) {
    Noh *y = x->direito;
    Noh *T2 = y->esquerdo;

    y->esquerdo = x;
    x->direito = T2;

    atualizaAltura(x);
    atualizaAltura(y);

    return y;
  }

  Noh *balancear(Noh *n) {
    atualizaAltura(n);
    int fb = fatorBalanceamento(n);

    if (fb > 1) {
      if (fatorBalanceamento(n->esquerdo) < 0) {
        n->esquerdo = rotacaoEsquerda(n->esquerdo);
      }
      return rotacaoDireita(n);
    }

    if (fb < -1) {
      if (fatorBalanceamento(n->direito) > 0) {
        n->direito = rotacaoDireita(n->direito);
      }
      return rotacaoEsquerda(n);
    }

    return n;
  }

  Noh *inserirAux(Noh *node, int valor) {
    if (!node) {
      return new Noh(valor);
    }
    if (valor < node->valor)
      node->esquerdo = inserirAux(node->esquerdo, valor);
    else
      node->direito = inserirAux(node->direito, valor);

    return balancear(node);
  }

  Noh *removerMenor(Noh *raizsub) {
    if (raizsub->esquerdo == nullptr) {
      return raizsub->direito;
    } else {
      raizsub->esquerdo = removerMenor(raizsub->esquerdo);
      return balancear(raizsub);
    }
  }

  Noh *removerAux(Noh *node, int valor) {
    if (node == nullptr) {
      cerr << "Noh não encontrado";
    }

    Noh *novaRaizSubArvore = node;

    if (valor < node->valor) {
      node->esquerdo = removerAux(node->esquerdo, valor);
    } else if (valor > node->valor) {
      node->direito = removerAux(node->direito, valor);
    } else {
      if (node->esquerdo == nullptr) {
        novaRaizSubArvore = node->direito;
      } else if (node->direito == nullptr) {
        novaRaizSubArvore = node->esquerdo;
      } else {
        novaRaizSubArvore = sucessor(node);
        novaRaizSubArvore->direito = removerMenor(node->direito);
        novaRaizSubArvore->esquerdo = node->esquerdo;
      }
      delete node;
    }

    return balancear(novaRaizSubArvore);
  }

  Noh *sucessor(Noh *node) {
    node = node->direito;
    while (node->esquerdo != nullptr)
      node = node->esquerdo;
    return node;
  }

  void emOrdemAux(Noh *node) {
    if (node) {
      emOrdemAux(node->esquerdo);
      cout << node->valor << " ";
      emOrdemAux(node->direito);
    }
  }

  void destruir(Noh *node) {
    if (node == nullptr)
      return;
    destruir(node->esquerdo);
    destruir(node->direito);
    delete node;
  }

public:
  AVL() : raiz(nullptr) {}
  ~AVL() {
    destruir(raiz);
    raiz = nullptr;
  }
  void inserir(int valor) { raiz = inserirAux(raiz, valor); }

  void remover(int valor) { raiz = removerAux(raiz, valor); }

  void emOrdem() {
    cout << "Em ordem: ";
    emOrdemAux(raiz);
    cout << endl;
  }
};

int main() {
  AVL arvore;
  arvore.inserir(10);
  arvore.inserir(20);
  arvore.inserir(30);
  arvore.inserir(40);
  arvore.inserir(50);
  arvore.remover(20);
  arvore.remover(30);
  arvore.inserir(25);

  arvore.emOrdem();
  return 0;
}