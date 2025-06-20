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
    cout << "[DEBUG] Rotacao Direita em " << y->valor << endl;
    Noh *x = y->esquerdo;
    Noh *T2 = x->direito;

    x->direito = y;
    y->esquerdo = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
  }

  Noh *rotacaoEsquerda(Noh *x) {
    cout << "[DEBUG] Rotacao Esquerda em " << x->valor << endl;
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
    cout << "[DEBUG] Balanceando " << n->valor << " (FB=" << fb << ")" << endl;

    if (fb > 1) {
      if (fatorBalanceamento(n->esquerdo) < 0) {
        cout << "[DEBUG] RL Case em " << n->valor << endl;
        n->esquerdo = rotacaoEsquerda(n->esquerdo);
      }
      return rotacaoDireita(n);
    }

    if (fb < -1) {
      if (fatorBalanceamento(n->direito) > 0) {
        cout << "[DEBUG] LR Case em " << n->valor << endl;
        n->direito = rotacaoDireita(n->direito);
      }
      return rotacaoEsquerda(n);
    }

    return n;
  }

  Noh *inserirRec(Noh *node, int valor) {
    if (!node) {
      cout << "[DEBUG] Inserindo " << valor << endl;
      return new Noh(valor);
    }
    cout << "[DEBUG] inserirRec: em " << node->valor << ", inserindo " << valor
         << endl;
    if (valor < node->valor)
      node->esquerdo = inserirRec(node->esquerdo, valor);
    else
      node->direito = inserirRec(node->direito, valor);

    return balancear(node);
  }

  void emOrdemRec(Noh *node) {
    if (node) {
      emOrdemRec(node->esquerdo);
      cout << node->valor << " ";
      emOrdemRec(node->direito);
    }
  }

public:
  AVL() : raiz(nullptr) {}

  void inserir(int valor) {
    cout << "\n[DEBUG] Chamando inserir(" << valor << ")" << endl;
    raiz = inserirRec(raiz, valor);
  }

  void emOrdem() {
    cout << "Em ordem: ";
    emOrdemRec(raiz);
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
  arvore.inserir(25);

  arvore.emOrdem();
  return 0;
}
