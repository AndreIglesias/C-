/*
AUTHOR      :
             Carlos Andre Iglesias 00084317
	     German Alexander Castro 00229017
	     Elsy Alejandra Chavez 00125717
DATE        : 26-10-17
DESCRIPTION : [PED] Parcial 2
 */
#include <iostream>

using namespace std;

template <class T>          //  Input into function with any type
T input(istream& stream){
  T i;
  stream >> i;
  return i;
}

inline int pModulo(int i, int n) {return (i % n + n) % n;}

///---------------------------------------------------------------------
typedef struct n{int dato; struct n* nxt=NULL;}node; // node structure
//--------------------------------------------------------------------

template <class NODE>
class List{
private:
  NODE* start;
public:
  List();
  NODE* createAuxNode(string);
  void append(NODE*);
  void insert(int, NODE*);
  void insertarInicio(NODE*);
  void print();
  void deleteNode(NODE*);
  void deleteList();
  int sum(NODE*);
  int callSum();
  void deploySum();
  void deleteInt(int);
  int size();
};
template <class NODE>
List<NODE>::List(){start=NULL;}

template <class NODE>
int List<NODE>::size(){
  int i=0;
  NODE* p=start;
  if(p)do{i++;p=p->nxt;}while(p);
  else cout << "La lista esta vacia" << endl<<endl;
  return i;
}

template <class NODE>
NODE* List<NODE>::createAuxNode(string prompt){
  cout<< prompt <<endl;
  NODE* NEW = new NODE;
  int aux;
  cout << "Entero: ";
  cin >> aux;
  NEW->dato=aux;
  return NEW;
}

template <class NODE>
int List<NODE>::sum(NODE* p){
  if(!start) return 0;
  if(!p->nxt) return p->dato;
  return p->dato+sum(p->nxt);
}

template <class NODE>
void List<NODE>::deploySum(){
  NODE* p=start;
  print();
  cout << endl << "Suma: " << sum(start) << endl;
  if(p){cout << p->dato;p=p->nxt;}
  while(p){cout << "+"<<p->dato;p=p->nxt;}
  if(start) cout << "=" << sum(start) << endl;
  //if(!start) cout << "La lista esta vacia" << endl<<endl;
}

template <class NODE>
int List<NODE>::callSum(){
  return sum(start);
}

template <class NODE>
void List<NODE>::deleteInt(int num){
  NODE* p=start;
  NODE* aux;
  if(!start)cout << "La lista esta vacia" << endl;
  else{
    while(p){
      if(p->dato==num){
	aux=p;
	deleteNode(p);
	p = aux->nxt;
      }
      else p=p->nxt;
    }
  }
}

template <class NODE>
void List<NODE>::deleteNode(NODE* p){
  if(p==start) start=p->nxt;
  else if(start){ // tie up the other nodes
    NODE* q=start;
    while(q && q->nxt){
      if(q->nxt==p){
	q->nxt=q->nxt->nxt;
      }
      q=q->nxt;
    }
  }
  // delete node
  cout << p <<endl;
  NODE* aa = p;
  p = new NODE; // empty node
  delete p;
  p = NULL;
}

template <class NODE>
void List<NODE>::deleteList(){
  NODE* p=start;
  if(p){
    do{deleteNode(p);p=p->nxt;}while(p);
    start=NULL;
  }
  else cout << "La lista esta vacia" << endl<<endl;
}


//partially specialize the entire template

template <class NODE>
void List<NODE>::insert(int pos, NODE* NEW){ //Insert by position
  if(!start || pos==0){
    NEW->nxt=start;
    start=NEW;
  }
  else if(pos+1==size() || pModulo(pos,size())==0) append(NEW);
  else{
    NODE* p=start;
    pos = pModulo(pos,size());
    for(int i=1; i<pos; i++)p=p->nxt;
    NEW->nxt=p->nxt;
    p->nxt=NEW;
  }
}

template <class NODE>
void List<NODE>::insertarInicio(NODE* NEW){insert(0,NEW);}

template <class NODE>
void List<NODE>::append(NODE* NEW){ //Inserting node at the end of the list
  if(!start){NEW->nxt=start;start=NEW;}
  else{
    NODE* p=start;
    while(p->nxt) p=p->nxt;
    p->nxt=NEW;
    NEW->nxt=NULL;
  }
}

template <class NODE>
void List<NODE>::print(){
  NODE* p=start;
  int i=1;
  cout << "------------------------------" << endl;
  while(p){cout<<endl<<"Nodo "<<(i++)<<endl<<"Entero: "<<p->dato<<endl;p=p->nxt;}
  if(!start) cout << "La lista esta vacia" << endl<<endl;
}

//----------------------------------------------------------
int main(){
  List<node> aux;
  int n;
  string str;
  int cant;
  cout << "Cuantos nodos desea crear?: ";
  cin >> cant;
  if(cant > 0){
    for(int i=0; i<cant; i++){
      str="Ingresar valores (";
      str+=to_string((i+1))+")";
      aux.insertarInicio(aux.createAuxNode(str));
      cout << endl;
    }
    aux.print();cout<<endl;
    cout << "Suma: " << aux.callSum() << endl << endl;
    cout << "Numero a borrar: ";
    cin >> n;
    aux.deleteInt(n);
    aux.deploySum();
  }
  else{cout << endl << "Valor invalido o 0"<< endl;
    cout << "No se puede hacer nada." << endl << endl;}
  return 0;
}
