/*                                                                                                                       
AUTHOR      : Andre I.                                                                                                   
DATE        : 23-10-17                                                                                                   
DESCRIPTION : Template for circular doubly linked list                                                                   
 */ 

#include <iostream>

using namespace std;

typedef struct n{
  int nFil,nCol;
  struct n* sigC=NULL;
  struct n* sigF=NULL;
  int dato;
}nodo;


class Matriz{
private:
  nodo* inicio;
public:
  Matriz();
  void Insertar(int, int);
  void Eliminar(int, int);
  void Mover(int, int, int, int);
  void Meter(int, int, nodo*);
};

Matriz::Matriz(){inicio=NULL;}

void Matriz::Meter(int fila, int columna, nodo* podo)
{
  if(inicio){
    nodo* p = inicio;
    bool col=false, fil=false;
    while(p->sigC){
      if(p->nCol==columna){
  col = true;
  break;
      }
      p = p->sigC;
    }
    if(!col){
      do{
  nodo* Nuevo = new nodo;
  Nuevo->nCol = p->nCol + 1;
  Nuevo->nFil = p->nFil;
  p->sigC = Nuevo;
  p = p->sigC;
      }while(p->nCol!=columna);
    }
    
    nodo* q = inicio;
    while(q->sigF){
      if(q->nFil==fila){
  fil = true;
  break;
      }
      q = q->sigF;
    }
    if(!fil){
      do{
  nodo* nuevo = new nodo;
  nuevo->nFil = q->nFil+1;
  nuevo->nCol = q->nCol;
  q->sigF = nuevo;
  q = q->sigF;
      }while(q->nFil!=fila);
    }

    podo->nCol = p->nCol;
    podo->nFil = q->nFil;
    nodo* auxP = p;
    nodo* auxQ = q;
    while(p->sigF && p->sigF->nFil<fila) p = p->sigF;
    while(q->sigC && q->sigC->nCol<columna) q = q->sigC;
    
    if(p->sigF) podo->sigF = p->sigF;
    else podo->sigC = auxP;
    p->sigF = podo;
    if(q->sigC) podo->sigC = q->sigC;
    else podo->sigF = auxQ;
    q->sigC = podo;
  }
  else{
    nodo* i = new nodo;
    i->nFil = 0;
    i->nCol = 0;
    inicio = i;
    Meter(fila, columna, podo);
  }
}

void Matriz::Insertar(int fila, int columna){
  if(inicio){
    nodo* p = inicio;
    bool col=false, fil=false;
    while(p->sigC){
      if(p->nCol==columna){
	col = true;
	break;
      }
      p = p->sigC;
    }
    if(!col){
      do{
	nodo* Nuevo = new nodo;
	Nuevo->nCol = p->nCol + 1;
	Nuevo->nFil = p->nFil;
	p->sigC = Nuevo;
	p = p->sigC;
      }while(p->nCol!=columna);
    }
    
    nodo* q = inicio;
    while(q->sigF){
      if(q->nFil==fila){
	fil = true;
	break;
      }
      q = q->sigF;
    }
    if(!fil){
      do{
	nodo* nuevo = new nodo;
	nuevo->nFil = q->nFil+1;
	nuevo->nCol = q->nCol;
	q->sigF = nuevo;
	q = q->sigF;
      }while(q->nFil!=fila);
    }
    nodo* nevo = new nodo;
    nevo->nCol = p->nCol;
    nevo->nFil = q->nFil;
    nodo* auxP = p;
    nodo* auxQ = q;
    while(p->sigF && p->sigF->nFil<fila) p = p->sigF;
    while(q->sigC && q->sigC->nCol<columna) q = q->sigC;
    
    if(p->sigF) nevo->sigF = p->sigF;
    else nevo->sigC = auxP;
    p->sigF = nevo;
    if(q->sigC) nevo->sigC = q->sigC;
    else nevo->sigF = auxQ;
    q->sigC = nevo;

    cout << "Ingrese entero: ";
    cin >> nevo->dato;
  }
  else{
    nodo* i = new nodo;
    i->nFil = 0;
    i->nCol = 0;
    inicio = i;
    Insertar(fila, columna);
  }
}

void Matriz::Eliminar(int fila, int columna){
  if(inicio){
    nodo* p = inicio;                                                                                                    
    bool col=false, fil=false;
    while(p){                      
      if(p->nCol==columna){                                                                                              
        col = true;                                                                                                      
        break;                                                                                                           
      }                                                                                                                  
      p = p->sigC;                                                                                                       
    }
    
    nodo* q = inicio;                                                                                                    
    while(q){                          
      if(q->nFil==fila){                                                                                                 
        fil = true;                                                                                                      
        break;                                                                                                           
      }                                                                                                                  
      q = q->sigF;                                                                                                       
    }
    
    if(!fil || !col) cout << "No existe ese nodo" << endl;
    else{
      while(p->sigF && p->sigF->nFil<fila) p = p->sigF;                                               
      while(q->sigC && q->sigC->nCol<columna) q = q->sigC;
          
      if(p->sigF && q->sigC && p->sigF->nFil==fila && q->sigC->nCol==columna && q->sigC==p->sigF){
	nodo* aBorrar = q->sigC;
	cout << "Dato del nodo a borrar: " << aBorrar->dato << endl;
	if(q->sigC->sigC) q->sigC = q->sigC->sigC;
	if(p->sigF->sigF) p->sigF = p->sigF->sigF;
	delete aBorrar;
	aBorrar = NULL;
      }
      
    }
  }
}

void Matriz::Mover(int fila, int columna, int fila2, int columna2)
{
  if(inicio){
    nodo* p = inicio;                                                                                                    
    bool col=false, fil=false;
    while(p){                      
      if(p->nCol==columna){                                                                                              
        col = true;                                                                                                      
        break;                                                                                                           
      }                                                                                                                  
      p = p->sigC;                                                                                                       
    }
    
    nodo* q = inicio;                                                                                                    
    while(q){                          
      if(q->nFil==fila){                                                                                                 
        fil = true;                                                                                                      
        break;                                                                                                           
      }                                                                                                                  
      q = q->sigF;                                                                                                       
    }
    
    if(!fil || !col) cout << "No existe ese nodo" << endl;
    else{
      while(p->sigF && p->sigF->nFil<fila) p = p->sigF;                                               
      while(q->sigC && q->sigC->nCol<columna) q = q->sigC;
          
      if(p->sigF && q->sigC && p->sigF->nFil==fila && q->sigC->nCol==columna && q->sigC==p->sigF){
  nodo* aMover = q->sigC;
  //cout << "Dato del nodo a borrar: " << aBorrar->dato << endl;
  if(q->sigC->sigC) q->sigC = q->sigC->sigC;
  if(p->sigF->sigF) p->sigF = p->sigF->sigF;
  
  Meter(fila2, columna2, aMover);
  cout << "dato: " << aMover->dato << " nueva fila " << aMover->nFil << " | nueva columna " << aMover->nCol << endl;
      }
      
    }
  }
}

int main(){
  Matriz objeto;
  int fil, col;
  cout << "Ingresar fila donde Insertar dato: ";
  cin >> fil;
  cout << "Ingresar columna donde Insertar dato: ";
  cin >> col;
  objeto.Insertar(fil,col);
  cout << "Ingresar fila donde Eliminar nodo: ";
  cin >> fil;
  cout << "Ingresar columna donde Eliminar nodo: ";
  cin >> col;
  objeto.Eliminar(fil,col);
  cout << "Ingresar fila del nodo a mover: ";
  cin >> fil;
  cout << "Ingresar columna del nodo a mover: ";
  cin >> col;
  int fil2, col2;
  cout << "Ingresar fila destino del nodo: ";
  cin >> fil2;
  cout << "Ingresar columna destino del nodo: ";
  cin >> col2;
  objeto.Mover(fil,col,fil2,col2);

  return 0;
}
