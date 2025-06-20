#include <iostream>

struct Noh {
  int valor;
  int altura;
  Noh *esquerdo;
  Noh *direito;

  Noh(int v) : valor(v), altura(0), esquerdo(nullptr), direito(nullptr) {}
};

class AVL {
private:
  Noh *raiz;

  int informaAltura(Noh *umNoh) {
    if (umNoh == nullptr) {
      return 0;
    } else {
      return umNoh->altura;
    }
  }

  void atualizaAltura(Noh *umNoh) {
    int altEsq = informaAltura(umNoh->esquerdo);
    int altDir = informaAltura(umNoh->direito);
    umNoh->altura = 1 + altEsq > altDir ? altEsq : altDir;
  }

  int fatorBalanceamento(Noh *umNoh) {
    return informaAltura(umNoh->esquerdo) - informaAltura(umNoh->direito);
  }

  Noh *rotacaoEsqueda(Noh *umNoh) {
    Noh *nohAux = umNoh->direito;
    umNoh->direito = nohAux->esquerdo;
    nohAux->esquerdo = umNoh;
    atualizaAltura(umNoh);
    atualizaAltura(nohAux);

    return nohAux;
  }

public:
};