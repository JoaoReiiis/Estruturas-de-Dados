#include <iostream>

using namespace std;

struct noh{
    int valor;
    noh *proximo;

    noh(int v){
        this->valor = v;
        proximo = nullptr;
    }
};

class Lista{
    noh *genesis;
    noh *apocalipse;
    int tamanho;

    public:
        Lista(){
            genesis = nullptr;
            apocalipse = nullptr;
            tamanho = 0;
        }

        void inserirEmListaVazia(int valor){
            noh *novo = new noh(valor);
            genesis = novo;
            apocalipse = novo;
            tamanho = 1;
        }

        void inserirNoInicioDaLista(int valor){
            if(this->vazia()){
                inserirEmListaVazia(valor);
            }else{
                noh *novo = new noh(valor);
                novo->proximo = genesis;
                genesis = novo;
                tamanho++;
            }
        }

        void inserirNoFimDaLista(int valor){
            if(this->vazia()){
                inserirEmListaVazia(valor);
            }else{
                noh *novo = new noh(valor);
                apocalipse->proximo = novo;
                apocalipse = novo;
                tamanho++;
            }
        }

        void inserirEmPosicao(int valor, int pos){
            if(this->vazia()){
                inserirEmListaVazia(valor);
            }else if(pos == 0){
                inserirNoInicioDaLista(valor);
            }else if(pos == this->tamanho){
                inserirNoFimDaLista(valor);
            }else{
                noh *novo = new noh(valor);
                noh *aux = genesis;
                int posAux = 0;

                while(posAux <  (pos - 1)){
                    aux = aux->proximo;
                    posAux++;
                }

                novo->proximo = aux->proximo;
                aux->proximo = novo;
                tamanho++;
            }
        }

        void percorrerLista(){
            noh *aux = genesis;

            while(aux != nullptr){
                aux = aux->proximo;
            }
        }

        bool buscarNaLista(int valor){
            noh *aux = genesis;
            bool existe = false;

            while(aux != nullptr){
                if(aux->valor == valor){
                    existe = true;
                    aux = nullptr;
                }else{
                    aux = aux->proximo;
                }
            }

            return existe;
        }

        noh* acessarPosicao(int pos){
            if(pos < 0  || pos >= tamanho) throw exception();
            noh *aux = genesis;
            int loc = 0;
            
            while(pos > loc){
                aux = aux->proximo;
                loc++;
            }
            return aux;
        }

        void imprimir(){
            noh *aux = genesis;

            while(aux!=nullptr){
                cout << aux->valor << " ";
                aux = aux->proximo;
            }
        }

        int removeNoInicio(){
            if(this->vazia()) throw exception();
            
            noh *aux = genesis;
            int valor = aux->valor;
            genesis = aux->proximo;
            delete aux;
            tamanho--;
            if(this->vazia())
                genesis = nullptr;
            return valor; 
        }

        int removeNoFim(){
            if(this->vazia()) throw exception();

            noh *aux = genesis;
            noh *anterior = nullptr;

            while(aux->proximo != nullptr){
                anterior = aux;
                aux = aux->proximo;
            }

            int valor = aux->valor;

            if(anterior == nullptr){
                genesis = nullptr;
                apocalipse = nullptr;
            }else{
                anterior->proximo = nullptr;
                apocalipse = anterior;
            }

            delete aux;
            tamanho--;
            return valor;
        }

        int removeEspecifico(int valor){
            if(this->vazia()) throw new exception;
            noh *aux = genesis;
            noh *anterior = nullptr;
            
            while(aux!=nullptr && aux->valor != valor){
                anterior = aux;
                aux = aux->proximo;
            }

            if(aux!=nullptr){
                if(aux == genesis){
                    removeNoInicio();
                }else if(aux == apocalipse){
                    removeNoFim();
                }else{
                    anterior->proximo = aux->proximo;
                    tamanho--;
                    delete aux;
                }
            }else{
                throw new exception;
            }
        } 

        void trocarDoisElementos(int pos1, int pos2){
            noh *ant1 = acessarPosicao(pos1-1);
            noh *aux1 = ant1->proximo;
            noh *ant2 = acessarPosicao(pos2-1);
            noh *aux2 = ant2->proximo;
            ant1->proximo = aux2;
            ant2->proximo = aux1;
            noh *posAux = aux1->proximo;
            aux1->proximo = aux2->proximo;
            aux2->proximo = posAux;
        }

        bool vazia(){
            return genesis == nullptr;
        }

        void teste(){
            cout << genesis->valor << endl << apocalipse->valor;
        }
};

int main(){
    int t = 100;
    Lista l;
    for(int i = 0; i < t; i++){
        l.inserirEmPosicao(i,i);
    }
    //l.removeNoFim();
    //l.removeNoInicio();
    cout << l.acessarPosicao(t-1)->valor;
    //l.imprimir();
}