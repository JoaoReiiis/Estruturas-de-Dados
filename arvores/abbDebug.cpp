#include <iostream>
using namespace std;

struct Noh {
  int valor;
  Noh *esquerdo;
  Noh *direito;
  Noh *pai;
  Noh(int v) : valor(v), esquerdo(nullptr), direito(nullptr), pai(nullptr) {}
};

class ABB {
private:
  Noh *raiz;

  Noh *inserirRecAux(Noh *umNoh, int umValor) {
    if (umNoh == nullptr) {
      cout << "[DEBUG] Inserindo novo nó com valor " << umValor << endl;
      return new Noh(umValor);
    }
    cout << "[DEBUG] inserirRecAux: nó atual = " << umNoh->valor
         << ", valor a inserir = " << umValor << endl;

    if (umValor < umNoh->valor) {
      cout << "  -> descendo à ESQUERDA de " << umNoh->valor << endl;
      Noh *novo = inserirRecAux(umNoh->esquerdo, umValor);
      umNoh->esquerdo = novo;
      novo->pai = umNoh;
    } else {
      cout << "  -> descendo à DIREITA de " << umNoh->valor << endl;
      Noh *novo = inserirRecAux(umNoh->direito, umValor);
      umNoh->direito = novo;
      novo->pai = umNoh;
    }
    return umNoh;
  }

  void percorreEmOrdemAux(Noh *umNoh) {
    if (umNoh != nullptr) {
      percorreEmOrdemAux(umNoh->esquerdo);
      cout << umNoh->valor << " ";
      percorreEmOrdemAux(umNoh->direito);
    }
  }

  Noh *removerRecAux(Noh *umNoh, int umValor) {
    if (umNoh == nullptr) {
      cout << "[DEBUG] Nó " << umValor << " não encontrado!" << endl;
      return nullptr;
    }
    cout << "[DEBUG] removerRecAux: nó atual = " << umNoh->valor
         << ", valor a remover = " << umValor << endl;

    if (umValor < umNoh->valor) {
      cout << "  -> descendo à ESQUERDA de " << umNoh->valor << endl;
      umNoh->esquerdo = removerRecAux(umNoh->esquerdo, umValor);
    } else if (umValor > umNoh->valor) {
      cout << "  -> descendo à DIREITA de " << umNoh->valor << endl;
      umNoh->direito = removerRecAux(umNoh->direito, umValor);
    } else {
      cout << "[DEBUG] Encontrado nó " << umNoh->valor << " para remoção"
           << endl;
      if (umNoh->esquerdo == nullptr) {
        cout << "  -> Nó tem apenas filho DIREITO ou é folha" << endl;
        Noh *temp = umNoh->direito;
        delete umNoh;
        return temp;
      } else if (umNoh->direito == nullptr) {
        cout << "  -> Nó tem apenas filho ESQUERDO" << endl;
        Noh *temp = umNoh->esquerdo;
        delete umNoh;
        return temp;
      } else {
        cout << "  -> Nó tem DOIS filhos, buscando sucessor" << endl;
        Noh *sucessor = minimoAux(umNoh->direito);
        cout << "     -> Sucessor é " << sucessor->valor << endl;
        umNoh->valor = sucessor->valor;
        umNoh->direito = removerRecAux(umNoh->direito, sucessor->valor);
      }
    }
    return umNoh;
  }

  Noh *minimoAux(Noh *raizSubArvore) {
    while (raizSubArvore->esquerdo != nullptr)
      raizSubArvore = raizSubArvore->esquerdo;
    return raizSubArvore;
  }

  void destruirNohRecursivamente(Noh *umNoh) {
    if (umNoh != nullptr) {
      destruirNohRecursivamente(umNoh->esquerdo);
      destruirNohRecursivamente(umNoh->direito);
      delete umNoh;
    }
  }

public:
  ABB() { raiz = nullptr; }
  ~ABB() { destruirNohRecursivamente(raiz); }

  void inserirRecursivamente(int umValor) {
    cout << "\n[DEBUG] Chamando inserirRecursivamente(" << umValor << ")\n";
    raiz = inserirRecAux(raiz, umValor);
  }

  void percorreEmOrdem() {
    cout << "Em ordem: ";
    percorreEmOrdemAux(raiz);
    cout << endl;
  }

  void removerRecursivamente(int umValor) {
    cout << "\n[DEBUG] Chamando removerRecursivamente(" << umValor << ")\n";
    raiz = removerRecAux(raiz, umValor);
  }
};

int main() {
  ABB arvore;
  arvore.inserirRecursivamente(15);
  arvore.inserirRecursivamente(6);
  arvore.inserirRecursivamente(18);
  arvore.inserirRecursivamente(1);
  arvore.inserirRecursivamente(8);
  arvore.inserirRecursivamente(7);
  arvore.inserirRecursivamente(21);

  arvore.percorreEmOrdem();

  arvore.removerRecursivamente(6);
  arvore.percorreEmOrdem();

  return 0;
}
