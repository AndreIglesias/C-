/*
AUTHOR      : Andre I.
DATE        : 20-10-17
DESCRIPTION : Template for singly-linked list
 */
#include <iostream>

using namespace std;

template <class T>          //  Input into function with any type
T input(istream& stream){
  T i;
  stream >> i;
  return i;
}

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
  AUX(); //CONSTRUCTOR
  
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

AUX::AUX(){
#define X(type, name) cout<<#name<<": ";set##name(input<type>(cin));
    KEY
    Attributes
#undef X
}
typedef struct n{AUX A;struct n* nxt=NULL;}node; // node structure
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
  void modify(); 
  void print();
  int size();
};
template <class NODE>
List<NODE>::List(){start=NULL;}

template<class NODE>
int List<NODE>::size(){
  int i=0;
  NODE* p=start;
  while(p){i++;p=p->nxt;}
  return i;
}
template <class NODE>
NODE* List<NODE>::createAuxNode(string prompt){
  cout<< prompt <<endl; NODE* NEW = new NODE; return NEW;
}

//partially specialize the entire template
#define getKEY(obj,a,key) obj.get##a()==key
template <class NODE>
void List<NODE>::modify(){
  node* p=start;
  bool keyExist=false;
#define X(type, name) \
  type keyw; \
  cout<< "Ingrese " << #name <<": ";	\
  cin >> keyw;\
  while(p){ \
    if(getKEY(p->A,name,keyw)){p->A.actualization();keyExist=true;}	\
    p=p->nxt;\
  }
  KEY
#undef X
    if(!keyExist){cout << "No existe ese campo!" << endl;modify();}
}

template <class NODE>
void List<NODE>::insert(int pos, NODE* NEW){ //Insert by position
  if(pos<size() && pos >= 0){
    if(!start || pos==0){
      NEW->nxt=start;
      start=NEW;
    }
    else{
      NODE* p=start;
      for(int i=1; i<pos; i++)p=p->nxt;
      NEW->nxt=p->nxt;
      p->nxt=NEW;
    }
  }
  else throw invalid_argument("INSERTION ERROR: position not in range");
}

template <class NODE>
void List<NODE>::append(NODE* NEW){ //Inserting node at the end of the list
  if(!start)start=NEW;
  else{
    NODE* p=start;
    while(p->nxt)p=p->nxt;
    p->nxt=NEW;
  }
}

template <class NODE>
void List<NODE>::print(){
  node* p=start;cout << "Lista desplegada" << endl;
  while(p){cout<<endl;p->A.show();p=p->nxt;}
}

//----------------------------------------------------------
int main(){
  List<node> aux;
  for(int i=0; i<2; i++){
    aux.append(aux.createAuxNode("Ingresar valores"));
    cout << endl;
  }
  aux.print();
  cout << "PARA MODIFICAR DATOS" << endl;
  aux.modify();
  aux.print();
  return 0;
}
