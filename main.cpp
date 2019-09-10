#include <iostream>
using namespace std;


template <typename T>
class nodo{
public:
    nodo<T> *sig;
    T n;
    nodo(T a){
        sig=0;
        n=a;
    }
};

template <typename T>
class listaabs{
protected:
    nodo<T> *ini;
    nodo<T> *fin;
    int tam;
public:
    listaabs(){
        ini=0;
        fin=0;
        tam=0;
    }
    void destruir(){
        nodo<T> *p;
        while(ini!=0){
            p=ini;
            ini=ini->sig;
            delete p;
        }
        fin=0;
        tam=0;
    }
    void inicializarlista(){
        destruir();
    }
    void imprimir(){
        nodo<T> *p=ini;
        while(p!=0){
            cout<<p->n<<" ";
            p=p->sig;
        }
        cout<<endl;
    }
    int tamano(){
        return tam;
    }
    T primero(){
        assert(ini!=0);
        return ini->n;
    }
    T ultimo(){
        assert(fin!=0);
        return fin->n;
    }
    void copia(listaabs<T>& lista2){
        nodo<T> *p;
        nodo<T> *q;
        if(ini!=0){
            destruir();
        }
        if(lista2.ini==0){
            ini=0;
            fin=0;
            tam=0;
        }else{
            p=lista2.ini;
            tam=lista2.tam;
            ini=new nodo<T>(p->n);
            fin=ini;
            p=p->sig;
            while(p!=0){
                q=new nodo<T>(p->n);
                fin->sig=q;
                fin=q;
                p=p->sig;
            }
        }
    }
    ~listaabs(){
        destruir();
    }
    listaabs<T>& operator=(listaabs<T>& lista2){
        if(this!=&lista2){
            copia(lista2);
        }
        return *this;
    }
    virtual bool buscar(T item, nodo<T>*& p, nodo<T>*& ant)=0;
    virtual void insertarprimero(T item)=0;
    virtual void insertarfinal(T item)=0;
    virtual bool borrar(T item)=0;
};

template <typename T>
class listadesordenada : public listaabs<T>{
public:
    bool buscar(T item, nodo<T>*& p, nodo<T>*& ant){
        p=this->ini;
        ant=this->ini;
        while(p!=0){
            if(p->n==item){
                return 1;
            }
            ant=p;
            p=p->sig;
        }
        return 0;
    }
    void insertarprimero(T item){
        nodo<T>* p=new nodo<T>(item);
        p->sig=this->ini;
        this->ini=p;
        this->tam++;
        if(this->fin==0){
            this->fin=p;
        }
    }
    void insertarfinal(T item){
        nodo<T>* p=new nodo<T>(item);
        if(this->ini==0){
            this->ini=p;
            this->fin=p;
            this->tam++;
        }else{
            this->fin->sig=p;
            this->fin=p;
            this->tam++;
        }
    }
    bool borrar(T item){
        nodo<T>* p;
        nodo<T>* ant;
        if(this->ini==0){
            return 0;
        }else if(this->ini==this->fin && this->ini->n==item){
            p=this->ini;
            this->ini=0;
            this->fin=0;
            delete this->ini;
            this->tam--;
            return 1;
        }else{
            if(buscar(item,p,ant)){
                if(p==this->ini){
                    this->ini=p->sig;
                    delete p;
                    return 1;
                }
                ant->sig=p->sig;
                delete p;
                this->tam--;
                return 1;
            }else{
                return 0;
            }
        }
        
        
    }
};

template <typename T>
class listaordenada : public listaabs<T>{
public:
    bool buscar(T item, nodo<T>*& p, nodo<T>*& ant){
        p=this->ini;
        ant=this->ini;
        while(p!=0){
            if(p->n==item){
                return 1;
            }
            ant=p;
            p=p->sig;
        }
        return 0;
    }
    void insertar(T item){
        nodo<T>* p=new nodo<T>(item);
        if(this->ini==0){
            this->ini=p;
            this->fin=p;
            this->tam++;
        }else if(this->ini==this->fin){
            if(item>this->ini->n){
                this->ini->sig=p;
                this->fin=p;
                this->tam++;
            }else{
                p->sig=this->ini;
                this->ini=p;
                this->tam++;
            }
        }else{
            nodo<T>* q=this->ini;
            if(item<=q->n){
                p->sig=this->ini;
                this->ini=p;
                this->tam++;
            }else{
                while(q->sig!=0 && item>q->sig->n){
                    q=q->sig;
                }
                p->sig=q->sig;
                q->sig=p;
                this->tam++;
                if(q==this->fin){
                    this->fin=p;
                }
            }
        }
    }
    void insertarprimero(T item){
        nodo<T>* p=new nodo<T>(item);
        p->sig=this->ini;
        this->ini=p;
        this->tam++;
        if(this->fin==0){
            this->fin=p;
        }
    }
    void insertarfinal(T item){
        nodo<T>* p=new nodo<T>(item);
        if(this->ini==0){
            this->ini=p;
            this->fin=p;
            this->tam++;
        }else{
            this->fin->sig=p;
            this->fin=p;
            this->tam++;
        }
    }
    bool borrar(T item){
        nodo<T>* p;
        nodo<T>* ant;
        if(this->ini==0){
            return 0;
        }else if(this->ini==this->fin && this->ini->n==item){
            p=this->ini;
            this->ini=0;
            this->fin=0;
            delete this->ini;
            this->tam--;
            return 1;
        }else{
            if(buscar(item,p,ant)){
                if(p==this->ini){
                    this->ini=p->sig;
                    delete p;
                    return 1;
                }
                ant->sig=p->sig;
                delete p;
                this->tam--;
                return 1;
            }else{
                return 0;
            }
        }
    }
};

int main(){
    cout<<"hola"<<endl;
    listaordenada<int> listita;
    listita.insertar(5);
    listita.insertar(1);
    listita.insertar(3);
    listita.insertar(9);

    listita.imprimir();
    listita.borrar(1);
    listita.imprimir();
    listita.insertar(3);
    listita.imprimir();
    
    return 0;
}