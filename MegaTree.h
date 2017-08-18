#include<iostream> 
#include<string> 
#include<vector>

struct MegaNode{ 
  std::string name; 
  int dimension; 
  double *vals; 
  MegaNode *left, *right; 
  MegaNode():name(""), dimension(0), vals(NULL), left(NULL), right(NULL) {}
  MegaNode(std::string str, int dim, double *values, MegaNode *l, MegaNode *r): 
    name(str),
    dimension(dim), 
    left(l), 
    right(r) 
  {
    vals = new double[ dim]; 
    for( int i= 0; i< dim; ++i) 
      vals[i]= values[i]; 
  }  
  MegaNode(std::string str, int dim, double *values): 
    name(str),
    dimension(dim), 
    left(NULL), 
    right(NULL)
  {
    vals = new double[ dim]; 
    for( int i= 0; i< dim; ++i) 
      vals[i]= values[i]; 
  } 
  
  MegaNode(const MegaNode& a): name(a.name), dimension(a.dimension), left(a.left), right(a.right)
  {
    vals = new double[ dimension]; 
    for( int i= 0; i< dimension; ++i) 
      vals[i]= a.vals[i]; 
  }
  MegaNode& operator=(const MegaNode & rhs){
    if(this != &rhs){
      name= rhs.name;
      dimension= rhs.dimension;
      double *new_vals = new double[dimension];
      for(int i=0; i< dimension; i++)
        new_vals[i]= rhs.vals[i]; 
      delete [] vals; 
      vals = new_vals; 
      left= rhs.left; 
      right= rhs.right; 

    }
    return *this;
  }
  ~MegaNode() { delete vals;  return; }
}; 


class MegaTree{ 
private: 
  MegaNode* head; 
  int dim; 
  void termsInPreOrder(MegaNode *N, int depth);
  MegaNode makeTree(std::vector<MegaNode> ls, int depth);
  double dist( double vals[], double rhs[], int len);
  MegaNode* NN(double vals[], MegaNode* cur, MegaNode* champ, int ndx);
  
public: 
  MegaTree( ): head(NULL), dim(2) { }   
  MegaTree(int d) : head(NULL), dim(d) {}
  MegaTree(int dim, std::string filename); 
  ~MegaTree(); 
  void insert( std::string name, double vals[] );
  void insert( MegaNode n);  
  void preorder(){ termsInPreOrder(head, 0); } 
  std::string nearestNode(double vals[]);
}; 
