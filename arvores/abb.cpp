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

    Noh* inserirAux(Noh* umNoh, int umValor) {
        if (umNoh == nullptr) {
            return new Noh(umValor);
        } else {
            if (umValor < umNoh->valor) {
                Noh* novo = inserirAux(umNoh->esquerdo, umValor);
                umNoh->esquerdo = novo;
                novo->pai = umNoh;
            } else {
                Noh* novo = inserirAux(umNoh->direito, umValor);
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

    Noh* removerAux(Noh* umNoh, int umValor) {
        if (umNoh == nullptr) {
            cout << "Nó não encontrado!" << endl;
            return nullptr;
        }

        if (umValor < umNoh->valor) {
            umNoh->esquerdo = removerAux(umNoh->esquerdo, umValor);
        } else if (umValor > umNoh->valor) {
            umNoh->direito = removerAux(umNoh->direito, umValor);
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
                umNoh->direito = removerAux(umNoh->direito, sucessor->valor);
            }
        }
        return umNoh;
    }

    void destruir(Noh* umNoh) {
        if (umNoh != nullptr) {
            destruir(umNoh->esquerdo);
            destruir(umNoh->direito);
            delete umNoh;
        }
    }

public:
    ABB() {
        raiz = nullptr;
    }

    ~ABB() {
        destruir(raiz);
    }

    void inserir(int umValor) {
        raiz = inserirAux(raiz, umValor);
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

    void remover(int umValor) {
        raiz = removerAux(raiz, umValor);
    }
};

int main() {
    ABB arvore;
    arvore.inserir(15);
    arvore.inserir(6);
    arvore.inserir(18);
    arvore.inserir(1);
    arvore.inserir(8);
    arvore.inserir(21);

    cout << "Em ordem: ";
    arvore.percorreEmOrdem();

    arvore.busca(8);
    arvore.busca(100);

    arvore.remover(6);
    cout << "Após remoção: ";
    arvore.percorreEmOrdem();

    cout << "Mínimo: " << arvore.minimo() << endl;
    cout << "Máximo: " << arvore.maximo() << endl;

    return 0;
}
