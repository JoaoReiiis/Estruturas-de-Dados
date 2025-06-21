#include <iostream>
using namespace std;

enum Cor { VERMELHO, PRETO };

struct Noh {
    int valor;
    Cor cor;
    Noh *esquerdo;
    Noh *direito;
    Noh *pai;

    Noh(int v) : valor(v), cor(VERMELHO), esquerdo(nullptr), direito(nullptr), pai(nullptr) {}
};

class ArvoreRubroNegra {
private:
    Noh *raiz;
    Noh *NIL;

    Noh* criarNIL() {
        Noh* nil = new Noh(0);
        nil->cor = PRETO;
        return nil;
    }

    void rotacaoEsquerda(Noh* x) {
        Noh *y = x->direito;
        x->direito = y->esquerdo;
        if (y->esquerdo != NIL) {
            y->esquerdo->pai = x;
        }
        y->pai = x->pai;
        if (x->pai == nullptr) {
            this->raiz = y;
        } else if (x == x->pai->esquerdo) {
            x->pai->esquerdo = y;
        } else {
            x->pai->direito = y;
        }
        y->esquerdo = x;
        x->pai = y;
    }

    void rotacaoDireita(Noh* y) {
        Noh *x = y->esquerdo;
        y->esquerdo = x->direito;
        if (x->direito != NIL) {
            x->direito->pai = y;
        }
        x->pai = y->pai;
        if (y->pai == nullptr) {
            this->raiz = x;
        } else if (y == y->pai->esquerdo) {
            y->pai->esquerdo = x;
        } else {
            y->pai->direito = x;
        }
        x->direito = y;
        y->pai = x;
    }

    void arrumarInsercao(Noh* z) {
        while (z != raiz && z->pai->cor == VERMELHO) {
            if (z->pai == z->pai->pai->esquerdo) {
                Noh* tio = z->pai->pai->direito;
                if (tio->cor == VERMELHO) {
                    z->pai->cor = PRETO;
                    tio->cor = PRETO;
                    z->pai->pai->cor = VERMELHO;
                    z = z->pai->pai;
                } else {
                    if (z == z->pai->direito) {
                        z = z->pai;
                        rotacaoEsquerda(z);
                    }
                    z->pai->cor = PRETO;
                    z->pai->pai->cor = VERMELHO;
                    rotacaoDireita(z->pai->pai);
                }
            } else {
                Noh* tio = z->pai->pai->esquerdo;
                if (tio->cor == VERMELHO) {
                    z->pai->cor = PRETO;
                    tio->cor = PRETO;
                    z->pai->pai->cor = VERMELHO;
                    z = z->pai->pai;
                } else {
                    if (z == z->pai->esquerdo) {
                        z = z->pai;
                        rotacaoDireita(z);
                    }
                    z->pai->cor = PRETO;
                    z->pai->pai->cor = VERMELHO;
                    rotacaoEsquerda(z->pai->pai);
                }
            }
        }
        raiz->cor = PRETO;
    }

    void destruir(Noh* node) {
        if (node == NIL) return;
        destruir(node->esquerdo);
        destruir(node->direito);
        delete node;
    }

    void percorreEmOrdemAux(Noh* node) {
        if (node != NIL) {
            percorreEmOrdemAux(node->esquerdo);
            cout << node->valor << " ";
            percorreEmOrdemAux(node->direito);
        }
    }

    void percorrePreOrdemAux(Noh* node) {
        if (node != NIL) {
            cout << node->valor << " ";
            percorreEmOrdemAux(node->esquerdo);
            percorreEmOrdemAux(node->direito);
        }
    }

    void percorrePosOrdemAux(Noh* node) {
        if (node != NIL) {
            percorreEmOrdemAux(node->esquerdo);
            percorreEmOrdemAux(node->direito);
            cout << node->valor << " ";
        }
    }

public:
    ArvoreRubroNegra() {
        NIL = criarNIL();
        raiz = NIL;
    }

    ~ArvoreRubroNegra() {
        destruir(raiz);
        delete NIL;
    }

    void inserir(int valor) {
        Noh* novo = new Noh(valor);
        novo->esquerdo = NIL;
        novo->direito = NIL;

        Noh* y = nullptr;
        Noh* x = raiz;

        while (x != NIL) {
            y = x;
            if (novo->valor < x->valor) {
                x = x->esquerdo;
            } else {
                x = x->direito;
            }
        }

        novo->pai = y;
        if (y == nullptr) {
            raiz = novo;
        } else if (novo->valor < y->valor) {
            y->esquerdo = novo;
        } else {
            y->direito = novo;
        }

        if (novo->pai == nullptr) {
            novo->cor = PRETO;
            return;
        }

        if (novo->pai->pai == nullptr) {
            return;
        }

        arrumarInsercao(novo);
    }

    void percorreEmOrdem() {
        percorreEmOrdemAux(raiz);
        cout << endl;
    }

    void percorrePreOrdem(){
        percorrePreOrdemAux(raiz);
        cout << endl;
    }

    void percorrePosOrdem(){
        percorrePosOrdemAux(raiz);
        cout << endl;
    }
};

int main() {
    ArvoreRubroNegra arvore;
    arvore.inserir(40);
    arvore.inserir(12);
    arvore.inserir(68);
    arvore.inserir(36);
    arvore.inserir(38);
    arvore.inserir(60);
    arvore.inserir(48);
    arvore.inserir(55);
    arvore.inserir(50);
    arvore.inserir(62);
    arvore.inserir(65);

    arvore.percorreEmOrdem();
    arvore.percorrePreOrdem();
    arvore.percorrePosOrdem();

    return 0;
}
