#include <sstream>
#include <string>
#include <iostream>
using namespace std;

struct node{
  int key;
  node *left;
  node *right;
};

  class tree{
public:
  tree();
  //~tree(); //----------------------------------------------------
  void insert(int key);
  node *search(int key);
  void destroy(); //destroy tree
  void showTree();
private:
  void destroy(node *leaf); //destroy tree
  void insert(int key, node *leaf);
  node *search(int key, node *leaf);
  void showTree(node *leaf, int nivel);
  node *root;
};

tree::tree(){root=NULL;}

void tree::destroy(node *leaf){
  if(leaf != NULL){
    destroy(leaf->left);
    destroy(leaf->right);
    delete leaf;
  }
}

void tree::insert(int key, node *leaf){
  if(key < leaf->key){
    if(leaf->left != NULL)
      insert(key, leaf->left);   //recursive
    else{
      leaf->left = new node;
      leaf->left->key = key;
      leaf->left->left= NULL;
      leaf->left->right=NULL;
    }
  }
  else if(key >= leaf->key){
    if(leaf->right!= NULL)
      insert(key, leaf->right);  //recursive
    else{
      leaf->right= new node;
      leaf->right->key = key;
      leaf->right->left= NULL;
      leaf->right->right=NULL;
    }
  }
}

void tree::insert(int key){
  if(root!=NULL) insert(key, root);
  else{
    root=new node;
    root->key=key;
    root->left=NULL;
    root->right=NULL;
  }
}

node *tree::search(int key, node *leaf){
  if(leaf!=NULL){
    if(key==leaf->key)
      return leaf;
    if(key < leaf->key)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
}

node *tree::search(int key){
  return search(key, root);
}

void tree::destroy(){destroy(root);}

void tree::showTree(){
  showTree(root, 0);
}

string operator*(const string& s, unsigned int n) {
  stringstream out;
  while (n--)
    out << s;
  return out.str();
}
string operator*(unsigned int n, const string& s) { return s * n; }

void tree::showTree(node *leaf, int nivel){
  string s="-- ";
  if(leaf!=NULL){
    cout << s*nivel << leaf->key << endl;
    if(leaf->left != NULL){
      //cout << "left ";
      cout << "L";
      showTree(leaf->left, nivel+1);
    }
    if(leaf->right != NULL){
      //cout << "right ";
      cout << "R";
      showTree(leaf->right, nivel+1);
    }
  }
}

int len(int *a){
  return (sizeof(a)-1);
}

int main(){
  tree arbol;
  int a[]={1,5,8,5,4,3,10,453,3,14,24,1};
  for(int i=0;i<12;i++) arbol.insert(a[i]);
  cout << endl;
  arbol.showTree();
  cout << endl;
  return 0;
}
 
