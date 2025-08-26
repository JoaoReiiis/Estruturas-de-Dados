#include <iostream>
#include <string>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        elemento *inicio;
        elemento *fim;
        int tamanho;
    public:
        lista();
        ~lista();        
        void insereInicio(int c);
        void insereFim (int c);
        void insereEmListaVazia(int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        bool vazia();
        void imprimeLista();
        bool buscaElemento(int c, elemento *aux);
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}
        
lista::~lista(){
}  

bool lista::vazia(){
    return inicio == nullptr;
}

void lista::insereEmListaVazia(int c){
    elemento *novo = new elemento(c);
    inicio = novo;
    fim = novo;
    tamanho = 1;
}

void lista::insereInicio (int c){
    if(this->vazia()){
        insereEmListaVazia(c);
    }else{
        elemento *novo = new elemento(c);
        novo->proximo = inicio;
        inicio->anterior = novo;
        inicio = novo;
        tamanho++;
    }
}
        
void lista::insereFim (int c){
    if(this->vazia()){
        insereEmListaVazia(c);
    }else{
        elemento *novo = new elemento(c);
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
        tamanho++;
    }
}

int lista::removeRepetidos(){
    if (vazia()) return 0;

    elemento *aux = inicio;
    while (aux) {
        elemento *aux2 = aux->proximo;
        while (aux2) {
            elemento *prox = aux2->proximo;
            if (aux2->chave == aux->chave) {
                if (aux2->anterior) aux2->anterior->proximo = aux2->proximo;
                else inicio = aux2->proximo;
                if (aux2->proximo) aux2->proximo->anterior = aux2->anterior;
                else fim = aux2->anterior;
                delete aux2;       
                tamanho--;           
            }
            aux2 = prox;  
        }
        aux = aux->proximo;
    }
    return tamanho;
}


        
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
            cout<<"VAZIA";
    }
}       
    
int main(){
    
    lista listaD;
    
    int chave;
    string dado;
    
    cin>>chave;
    
    while (chave != -1){
        listaD.insereFim(chave);        
        cin>>chave;  
    }
    cout<<listaD.removeRepetidos()<<endl;
    listaD.imprimeLista();
    
    
    return 0;
}

