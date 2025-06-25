#include <iostream>
#include <algorithm>

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

    int altura(Noh *n) {
        if (n == nullptr) return 0;
        return n->altura;
    }

    void atualizaAltura(Noh *n) {
        if (n != nullptr) {
            n->altura = 1 + max(altura(n->esquerdo), altura(n->direito));
        }
    }

    int fatorBalanceamento(Noh *n) {
        if (n == nullptr) return 0;
        return altura(n->esquerdo) - altura(n->direito);
    }

    Noh* rotacaoDireita(Noh *y) {
        Noh *x = y->esquerdo;
        Noh *T2 = x->direito;

        x->direito = y;
        y->esquerdo = T2;

        atualizaAltura(y);
        atualizaAltura(x);

        return x;
    }

    Noh* rotacaoEsquerda(Noh *x) {
        Noh *y = x->direito;
        Noh *T2 = y->esquerdo;

        y->esquerdo = x;
        x->direito = T2;

        atualizaAltura(x);
        atualizaAltura(y);

        return y;
    }

    Noh* balancear(Noh *n) {
        if (n == nullptr) return nullptr;

        atualizaAltura(n);
        int fb = fatorBalanceamento(n);

        if (fb > 1 && fatorBalanceamento(n->esquerdo) >= 0) {
            return rotacaoDireita(n);
        }

        if (fb < -1 && fatorBalanceamento(n->direito) <= 0) {
            return rotacaoEsquerda(n);
        }

        if (fb > 1 && fatorBalanceamento(n->esquerdo) < 0) {
            n->esquerdo = rotacaoEsquerda(n->esquerdo);
            return rotacaoDireita(n);
        }

        if (fb < -1 && fatorBalanceamento(n->direito) > 0) {
            n->direito = rotacaoDireita(n->direito);
            return rotacaoEsquerda(n);
        }

        return n;
    }

    Noh* buscaAux(Noh *noh, int valor) {
        if (noh == nullptr) return nullptr;
        if (valor == noh->valor) return noh;
        if (valor < noh->valor) return buscaAux(noh->esquerdo, valor);
        return buscaAux(noh->direito, valor);
    }

    Noh* inserirAux(Noh *noh, int valor) {
        if (noh == nullptr) {
            return new Noh(valor);
        }

        if (valor < noh->valor) {
            noh->esquerdo = inserirAux(noh->esquerdo, valor);
        } else if (valor > noh->valor) {
            noh->direito = inserirAux(noh->direito, valor);
        } else {
            return noh; // Não permite valores duplicados
        }

        return balancear(noh);
    }

    Noh* removerAux(Noh *noh, int valor) {
        if (noh == nullptr) return nullptr;

        if (valor < noh->valor) {
            noh->esquerdo = removerAux(noh->esquerdo, valor);
        } else if (valor > noh->valor) {
            noh->direito = removerAux(noh->direito, valor);
        } else {
            Noh *temp;
            if (noh->esquerdo == nullptr || noh->direito == nullptr) {
                temp = (noh->esquerdo != nullptr) ? noh->esquerdo : noh->direito;

                if (temp == nullptr) {
                    temp = noh;
                    noh = nullptr;
                } else {
                    *noh = *temp;
                }
                delete temp;
            } else {
                temp = minimoAux(noh->direito);
                noh->valor = temp->valor;
                noh->direito = removerAux(noh->direito, temp->valor);
            }
        }

        if (noh == nullptr) return nullptr;

        return balancear(noh);
    }

    Noh* minimoAux(Noh *noh) {
        while (noh != nullptr && noh->esquerdo != nullptr) {
            noh = noh->esquerdo;
        }
        return noh;
    }

    Noh* maximoAux(Noh *noh) {
        while (noh != nullptr && noh->direito != nullptr) {
            noh = noh->direito;
        }
        return noh;
    }

  /*Percorrimento em Ordem:
  Ordem de Visita: Esquerda, Raiz, Direita.
  Utilizado para acessar os elementos de uma árvore binária de busca em ordem
  crescente.*/
  void percorreEmOrdemAux(Noh *umNoh) {
    if (umNoh != nullptr) {
      percorreEmOrdemAux(umNoh->esquerdo);
      cout << umNoh->valor << " ";
      percorreEmOrdemAux(umNoh->direito);
    }
  }

  /*Percorrimento Pre-Ordem:
  Ordem de Visita: Raiz, Esquerda, Direita.
  A raiz é visitada primeiro, seguido pelos nós esquerda e direita. Útil para
  operações como cópia de árvores.*/
  void percorrePreOrdemAux(Noh *umNoh) {
    if (umNoh != nullptr) {
      cout << umNoh->valor << " ";
      percorrePreOrdemAux(umNoh->esquerdo);
      percorrePreOrdemAux(umNoh->direito);
    }
  }

  /*Percorrimento Pos-Ordem:
  Ordem de Visita: Esquerda, Direita, Raiz.
  Visita os nós filhos antes do nó raiz, sendo útil em operações que precisam
  processar os filhos antes da raiz.*/
  void percorrePosOrdemAux(Noh *umNoh) {
    if (umNoh != nullptr) {
      percorrePosOrdemAux(umNoh->esquerdo);
      percorrePosOrdemAux(umNoh->direito);
      cout << umNoh->valor << " ";
    }
  }

    void destruir(Noh *noh) {
        if (noh != nullptr) {
            destruir(noh->esquerdo);
            destruir(noh->direito);
            delete noh;
        }
    }

public:
    AVL() : raiz(nullptr) {}

    ~AVL() {
        destruir(raiz);
    }

    void inserir(int valor) {
        raiz = inserirAux(raiz, valor);
    }

    void remover(int valor) {
        raiz = removerAux(raiz, valor);
    }

    void busca(int valor) {
        Noh *resultado = buscaAux(raiz, valor);
        if (resultado == nullptr) {
            cout << "Elemento não encontrado!!!" << endl;
        } else {
            cout << "Elemento encontrado: " << resultado->valor << endl;
        }
    }

    int minimo() {
        if (raiz == nullptr) throw runtime_error("Árvore vazia");
        return minimoAux(raiz)->valor;
    }

    int maximo() {
        if (raiz == nullptr) throw runtime_error("Árvore vazia");
        return maximoAux(raiz)->valor;
    }

    void percorreEmOrdem() {
        cout << "Em ordem: ";
        percorreEmOrdemAux(raiz);
        cout << endl;
    }

    void percorrePreOrdem() {
        cout << "Pré-ordem: ";
        percorrePreOrdemAux(raiz);
        cout << endl;
    }

    void percorrePosOrdem() {
        cout << "Pós-ordem: ";
        percorrePosOrdemAux(raiz);
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

    arvore.percorreEmOrdem();
    arvore.percorrePreOrdem();
    arvore.percorrePosOrdem();

    arvore.busca(25);
    arvore.busca(30);

    cout << "Mínimo: " << arvore.minimo() << endl;
    cout << "Máximo: " << arvore.maximo() << endl;

    return 0;
}
