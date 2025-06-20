#include <iostream>
using namespace std;

struct Noh {
    int valor;
    Noh* esquerdo;
    Noh* direito;
    Noh* pai;

    Noh(int v) : valor(v), esquerdo(nullptr), direito(nullptr), pai(nullptr) {}
};

class ABB {
private:
    Noh* raiz;

    Noh* inserirRecAux(Noh* umNoh, int umValor) {
        if (umNoh == nullptr) {
            return new Noh(umValor);
        } else {
            if (umValor < umNoh->valor) {
                Noh* novo = inserirRecAux(umNoh->esquerdo, umValor);
                umNoh->esquerdo = novo;
                novo->pai = umNoh;
            } else {
                Noh* novo = inserirRecAux(umNoh->direito, umValor);
                umNoh->direito = novo;
                novo->pai = umNoh;
            }
            return umNoh;
        }
    }

    Noh* minimoAux(Noh* raizSubArvore) {
        while (raizSubArvore->esquerdo != nullptr)
            raizSubArvore = raizSubArvore->esquerdo;
        return raizSubArvore;
    }

    Noh* maximoAux(Noh* raizSubArvore) {
        while (raizSubArvore->direito != nullptr)
            raizSubArvore = raizSubArvore->direito;
        return raizSubArvore;
    }

    void percorreEmOrdemAux(Noh* umNoh) {
        if (umNoh != nullptr) {
            percorreEmOrdemAux(umNoh->esquerdo);
            cout << umNoh->valor << " ";
            percorreEmOrdemAux(umNoh->direito);
        }
    }

    Noh* buscaAux(int umValor) {
        Noh* atual = raiz;
        while (atual != nullptr) {
            if (atual->valor == umValor) {
                return atual;
            } else if (umValor < atual->valor) {
                atual = atual->esquerdo;
            } else {
                atual = atual->direito;
            }
        }
        return nullptr;
    }

    void transplanta(Noh* antigo, Noh* novo) {
        if (antigo == raiz) {
            raiz = novo;
        } else if (antigo == antigo->pai->esquerdo) {
            antigo->pai->esquerdo = novo;
        } else {
            antigo->pai->direito = novo;
        }
        if (novo != nullptr) {
            novo->pai = antigo->pai;
        }
    }

    Noh* removerRecAux(Noh* umNoh, int umValor) {
        if (umNoh == nullptr) {
            cout << "Nó não encontrado!" << endl;
            return nullptr;
        }

        if (umValor < umNoh->valor) {
            umNoh->esquerdo = removerRecAux(umNoh->esquerdo, umValor);
        } else if (umValor > umNoh->valor) {
            umNoh->direito = removerRecAux(umNoh->direito, umValor);
        } else {
            if (umNoh->esquerdo == nullptr) {
                Noh* temp = umNoh->direito;
                delete umNoh;
                return temp;
            } else if (umNoh->direito == nullptr) {
                Noh* temp = umNoh->esquerdo;
                delete umNoh;
                return temp;
            } else {
                Noh* sucessor = minimoAux(umNoh->direito);
                umNoh->valor = sucessor->valor;
                umNoh->direito = removerRecAux(umNoh->direito, sucessor->valor);
            }
        }
        return umNoh;
    }

    void destruirNohRecursivamente(Noh* umNoh) {
        if (umNoh != nullptr) {
            destruirNohRecursivamente(umNoh->esquerdo);
            destruirNohRecursivamente(umNoh->direito);
            delete umNoh;
        }
    }

public:
    ABB() {
        raiz = nullptr;
    }

    ~ABB() {
        destruirNohRecursivamente(raiz);
    }

    void inserirRecursivamente(int umValor) {
        raiz = inserirRecAux(raiz, umValor);
    }

    void percorreEmOrdem() {
        percorreEmOrdemAux(raiz);
        cout << endl;
    }

    void busca(int umValor) {
        Noh* resultado = buscaAux(umValor);
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

    void removerRecursivamente(int umValor) {
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
    arvore.inserirRecursivamente(21);

    cout << "Em ordem: ";
    arvore.percorreEmOrdem();

    arvore.busca(8);
    arvore.busca(100);

    arvore.removerRecursivamente(6);
    cout << "Após remoção: ";
    arvore.percorreEmOrdem();

    cout << "Mínimo: " << arvore.minimo() << endl;
    cout << "Máximo: " << arvore.maximo() << endl;

    return 0;
}
