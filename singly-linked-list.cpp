/*
AUTHOR      : Andre I.
DATE        : 23-10-17
DESCRIPTION : Template for circular doubly linked list
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
//! Attributes of the AUX class
#define Attributes \
  X(long int, entero1)				\
  X(long int, entero2)				\
  X(string, cadena3)

#define KEY \
  X(long int, key) 
  
class AUX{
private:
#define X(type, name) type name;
  KEY
  Attributes
#undef X
  public:
  AUX(){} //CONSTRUCTOR
  AUX(bool);
  
  // GET & SET METHODS
#define X(type, name) void set##name(type param){name = param;};type get##name(){return name;}
  KEY
  Attributes
#undef X
  
  // SHOW ALL ELEMENTS
  void show(){
#define X(type, name) cout<<#name<<": "<<get##name()<<endl;
    KEY
    Attributes
#undef X
      }
  void actualization(){
    show();cout << endl;
    string NAME="";
    bool existeCampo;
    do{
      existeCampo=false;
      cout << "Nombre del campo a actualizar (0 para salir): ";
      cin >> NAME;
      if(NAME!="0"){
#define X(type, name) if(#name==NAME){cout << "Nuevo valor: "; cin >> name;existeCampo=true;}
	KEY
	Attributes
#undef X
	  if(!existeCampo)cout << "Campo con crisis existencial!" << endl;
	  }
    }while(NAME!="0");
  }
};
AUX::AUX(bool n){
#define X(type, name) cout<<#name<<": ";set##name(input<type>(cin));
    Attributes
#undef X
}
typedef struct n{AUX A;struct n* nxt=NULL; struct n* prev=NULL; n();n(bool){};}node; // node structure
n::n(){AUX B(true);A=B;}
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
  void modify(int);
#define X(type, name) bool keyExist(type);type inputKey();
  KEY
#undef X
  void print();
  void deleteNode(NODE*);
  void deleteList();
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
#define X(type, name)				\
  type List<NODE>::inputKey(){			\
    type key=input<type>(cin);			\
    bool KEYExist=keyExist(key);		\
    while(KEYExist){							\
      cout << "Se ha encontrado una coincidencia de: " << key << endl;	\
      cout << "Introduzca otro dato: ";					\
      key=input<type>(cin);						\
      KEYExist=keyExist(key);						\
    }									\
    return key;								\
  }
KEY
#undef X

template <class NODE>
NODE* List<NODE>::createAuxNode(string prompt){
  cout<< prompt <<endl;
#define X(type, name) cout<<#name<<": "; type key = inputKey();		\
  NODE* NEW = new NODE;							\
  NEW->A.set##name(key);
  KEY
#undef X
  return NEW;
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
  p = new NODE(false); // empty node
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

template <class NODE>
#define X(type, name) \
  bool List<NODE>::keyExist(type key){		\
    if(!start) return false;			\
    else{					\
      NODE* p=start;				\
      while(p){					\
	if(p->A.get##name()==key) return true;	\
	p=p->nxt;				\
      }						\
    }						\
    return false;				\
  }
  KEY
#undef X

//partially specialize the entire template
#define getKEY(obj,a,key) obj.get##a()==key
template <class NODE>
void List<NODE>::modify(int op){
  //! (op==0) ? actualizar : eliminar nodo
  NODE* p=start;
  bool KeyExist=false;
  if(p){
#define X(type, name)							\
    type keyw;								\
    cout<< "Ingrese " << #name <<": ";					\
    cin >> keyw;							\
    while(p){if(getKEY(p->A,name,keyw))					\
	{KeyExist=true; if(op==0)p->A.actualization();else {deleteNode(p);break;}} \
      p=p->nxt;}
    KEY
#undef X
      if(!KeyExist){cout << "No existe esa llave!" << endl;modify(op);}
  }
  else cout << "La lista esta vacia" << endl<<endl;
}

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
void List<NODE>::append(NODE* NEW){ //Inserting node at the end of the list
  if(!start){NEW->nxt=start;NEW->prev=start;start=NEW;}
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
  while(p){cout<<endl;p->A.show();p=p->nxt;}
  if(!start) cout << "La lista esta vacia" << endl<<endl;
}

//----------------------------------------------------------
int main(){
  List<node> aux;
  int n;
  string str;
  do{
    cout << "--------------------------------" << endl;
    cout << "1) Ingresar datos" << endl;
    cout << "2) Mostrar datos" << endl;
    cout << "3) Actualizar datos" << endl;
    cout << "4) Insertar en una posicion" << endl;
    cout << "5) Mostrar tamano lista" << endl;
    cout << "6) Eliminar nodo" << endl;
    cout << "7) Eliminar toda la lista" << endl;
    cout << "0) Salir" << endl;
    cout << ">> ";
    cin >> n;
    switch(n){
    case 1:{
      int cant;
      cout << "Cuantos nodos desea crear?: ";
      cin >> cant;
      for(int i=0; i<cant; i++){
	str="Ingresar valores (";
	str+=to_string((i+1))+")";
	aux.append(aux.createAuxNode(str));
	cout << endl;
      }
      break;
    }
    case 2:{aux.print();cout<<endl;break;}
    case 3:{aux.modify(0);break;} // actualization
    case 4:{
      int pos;
      cout <<"Posicion a ingresar: ";
      cin >> pos;
      if(pos==0)pos++;
      if(pos>0)pos--;
      aux.insert(pos, aux.createAuxNode("Ingresar valores"));
      break;
    }
    case 5:{cout << "size: " << aux.size() << endl<<endl; break;}
    case 6: {aux.modify(1);break;} // deleteNode
    case 7: {aux.deleteList();break;}
    case 0: {break;}
    default:{cout << "La eleccion debe estar entre 0 y 7" << endl;break;}
    }
  }while(n!=0);
  return 0;
}
