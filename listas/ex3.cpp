#include <iostream>

using namespace std;

struct noh {
  string comando;
  noh *proximo;
  noh *anterior;

  noh(string c) {
    this->comando = c;
    proximo = nullptr;
    anterior = nullptr;
  }
};

class Lista {
  noh *genesis;
  noh *apocalipse;
  int tamanho;
  int capacidade;

public:
  Lista(int c) {
    genesis = nullptr;
    apocalipse = nullptr;
    tamanho = 0;
    capacidade = c;
  }

  void inserirEmListaVazia(string comando) {
    noh *novo = new noh(comando);
    genesis = novo;
    apocalipse = novo;
    tamanho = 1;
  }

  void inserirNoFimDaLista(string comando) {
    if (this->vazia()) {
      inserirEmListaVazia(comando);
    } else {
      if (tamanho == capacidade) {
        noh *aux = genesis;
        genesis = aux->proximo;
        genesis->anterior = nullptr;
        cout << "esqueci: " << aux->comando << endl;
        delete aux;
        tamanho--;
      }

      noh *novo = new noh(comando);
      apocalipse->proximo = novo;
      novo->anterior = apocalipse;
      apocalipse = novo;
      tamanho++;
    }
  }

  void undo() {
    if (!this->vazia()) {
      noh *aux = apocalipse;
      apocalipse = aux->anterior;
      if(apocalipse != nullptr){
        apocalipse->proximo = nullptr;
      }else{
        genesis = nullptr;
      }
      cout << "desfazer: " << aux->comando << endl;
      delete aux;
      tamanho--;
    } else {
      cout << "ERRO" << endl;
    }
  }

  bool vazia() { return this->genesis == nullptr; }
};

int main() {
    int c;
    cin >> c;
    cin.ignore();
    Lista l(c);
    string linha = "";
   do{
        getline(cin,linha);
        if (linha == "undo") {
            l.undo();
        } else if(linha != "sair"){
            l.inserirNoFimDaLista(linha);
        }
    }while(linha != "sair");
}