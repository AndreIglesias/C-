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

//---------------------------------------------------------------------
// Attributes of the AUX class
#define Attributes\
 X(long int, entero1, 4090)				\
 X(long int, entero2, 5050)				\
 X(string, cadena3, "FOO")

class AUX{
private:
#define X(type, name, value) type name = value;
  Attributes
#undef X
  public:
#define X(type, name, value) void set##name(type param){name = param;};type get##name(){return name;}
  Attributes
#undef X
  void show(){
#define X(type, name, value) cout<<#name<<": "<<get##name()<<endl;
  Attributes
#undef X
  }
};
typedef struct n{AUX A;struct n* nxt=NULL;}node; // node structure
//--------------------------------------------------------------------

class List{
private:
  node* start;
public:
  List();
  node* createAuxNode(string);
  void append(node*);
  void insert(int, node*);
  void print();
  int size();
};
List::List(){start=NULL;}

int List::size(){
  int i=0;
  node* p=start;
  while(p){i++;p=p->nxt;}
  return i;
}

node* List::createAuxNode(string prompt="Ingresar valores"){
  node* NEW = new node; cout<< prompt <<endl;
#define X(type, name, value) cout<<#name<<": ";NEW->A.set##name(input<type>(cin));
  Attributes
#undef X
  return NEW;
}

void List::insert(int pos, node* NEW){ //Insert by position
  if(pos<size() && pos >= 0){
    if(!start || pos==0){
      NEW->nxt=start;
      start=NEW;
    }
    else{
      node* p=start;
      for(int i=1; i<pos; i++)p=p->nxt;
      NEW->nxt=p->nxt;
      p->nxt=NEW;
    }
  }
  else throw invalid_argument("INSERTION ERROR: position not in range");
}

void List::append(node* NEW){ //Inserting node at the end of the list
  if(!start)start=NEW;
  else{
    node* p=start;
    while(p->nxt)p=p->nxt;
    p->nxt=NEW;
  }
}

void List::print(){
  node* p=start;
  while(p){cout<<endl;p->A.show();p=p->nxt;}
}

//----------------------------------------------------------
int main(){
  List aux;
  for(int i=0; i<3; i++){
    aux.append(aux.createAuxNode());
    cout << endl;
  }
  aux.print();
  return 0;
}
