#include "MegaTree.h"
#include <fstream>
#include <vector> 
#include <string> 
#include<cstring>
#include<cmath>

int partition(std::vector<MegaNode> &arr, int depth, int top, int bottom){
    MegaNode pivot= arr[top];
    std::vector<MegaNode> left;
    std::vector<MegaNode> right;
    for( int i= top+1; i <= bottom; i++) {
        if(arr[i].vals[depth] <= pivot.vals[depth]) left.push_back(arr[i]);
        else right.push_back(arr[i]);
    }
    
    for( int i= 0; i < left.size(); i++)
        arr[top+i]= left[i];

    int ppos = top + left.size();
    arr[ppos ]= pivot; 
    for(int i= 0; i < right.size(); i++){
        arr[ ppos +i +1] = right[i];
    }
    return ppos;

}

void quickSort(std::vector <MegaNode> &arr, int top, int bottom, int depth) {
    if(bottom <= top) return;

    int middle = partition(arr, depth, top, bottom);
    quickSort(arr, top, middle-1, depth);
    quickSort(arr, middle+1, bottom, depth);        
    
}

int fmedian( std::vector<MegaNode> &arr, int depth){

  quickSort(arr, 0, arr.size()-1, depth);
  int mid= arr.size()/2; 
  return mid;

}

MegaTree::MegaTree( int dim, std::string filename): head(NULL), dim(dim)
{
  char *cstr = new char [filename.length()+1];
  std::strcpy (cstr, filename.c_str()); 
  std::ifstream fin;
  if(!fin){
    std::cerr<<"Error writing file... Exiting now.\n";
    //exit(1); 
  }  
  fin.open(cstr); 
  int numOfRecords= 5; 
  fin >> numOfRecords; 
  //std::cout<<"# of records: "<< numOfRecords<<std::endl;
  
  std::vector<MegaNode> points; 
  for( int i =0; i < numOfRecords; i++)
  {
    std::string record; 
    double vals[dim];
    fin >> record;
    //std::cout <<record<< std::endl;
    for(int j=0; j<dim; j++)
      fin >> vals[j]; 
    points.push_back( MegaNode(record, dim, vals) );
  }
  // std::cout<<"1st point: ";
  //for(int i=0; i< dim; i++) std::cout<< points[0].vals[i] << " "; 
  //std::cout << std::endl;
  //int ndx =0;
  head = new MegaNode( makeTree(points, 0));
 /* while(points.size() >=1){

    int median = fmedian(points, ndx); 
  //std::cout<<"Median: " <<median.name<<std::endl;
    insert(points[median]);
    points.erase( points.begin() + median);
    ndx= (ndx+1)%dim;
  }*/
  //fin.close(); 
  
}
 
MegaNode MegaTree::makeTree(std::vector<MegaNode> ls, int depth){

 //  if(ls.size()== 1) return &ls[0]; 
  //int axis = depth% dim; 
  //fmedian sorts vector gives median ndx
  int median = fmedian(ls, depth);
  std::vector<MegaNode> left, right; 
  MegaNode N(ls[median]);
  for(int i=0; i< ls.size(); i++)
  {
    if(i < median) left.push_back(ls[i]); 
    if(i > median) right.push_back(ls[i]);

  }
  if(left.size() >0) N.left= new MegaNode( makeTree( left, ++depth%dim)); 
  if(right.size() >0) N.right= new MegaNode( makeTree(right, ++depth%dim));  
 
  return N;
}
 
void deleteNode(MegaNode *N){
  
  if (N== NULL) return; 
  deleteNode(N->left); 
  deleteNode(N->right); 
  delete N; 

}

MegaTree::~MegaTree(){
  deleteNode(head); 
}


void MegaTree::insert(std::string name, double vals[]){
  MegaNode *cur= head; 
  if(cur == NULL){
    head= new MegaNode(name, dim, vals); 
    return; 
  } 
  int ndx= 0; 
  int treeDepth = 0; 
  while(true){ 
    ndx = treeDepth % dim; 
    if( vals[ndx] < cur->vals[ndx] ){ 
      if( cur->left == NULL){
        cur->left = new MegaNode(name, dim, vals); 
        return; 
      }
      else cur = cur->left; 
    } 
    else if( vals[ndx] >= cur->vals[ndx] ){
      if( cur->right == NULL ){
        cur->right= new MegaNode(name, dim, vals); 
        return; 
      } 
      else cur = cur->right;   
    } 
    ++treeDepth;
  } 


}

void MegaTree::insert(MegaNode n){
  MegaNode *cur= head; 
  if(cur == NULL){
    head= new MegaNode(n); 
    return; 
  } 
  int ndx= 0; 
  int treeDepth = 0; 
  while(true){ 
    ndx = treeDepth % dim; 
    if( n.vals[ndx] < cur->vals[ndx] ){ 
      if( cur->left == NULL){
        cur->left = new MegaNode(n); 
        return; 
      }
      else cur = cur->left; 
    } 
    else if( n.vals[ndx] >= cur->vals[ndx] ){
      if( cur->right == NULL ){
        cur->right= new MegaNode(n); 
        return; 
      } 
      else cur = cur->right;   
    } 
    ++treeDepth;
  } 


}

void MegaTree::termsInPreOrder(MegaNode *N, int depth){
  if( N== NULL) return; 
  std::cout<< N->name<< ": "; 
  for(int i=0; i <dim; i++) std::cout <<N->vals[i] << " ";
  std::cout<< std::endl;
  termsInPreOrder(N->left, ++depth); 
  termsInPreOrder(N->right, ++depth); 
}


std::string MegaTree::nearestNode(double vals[]){
  MegaNode* best = NN( vals, head, NULL, 0); 
  return best->name;   
}

MegaNode* MegaTree::NN(double vals[], MegaNode* cur, MegaNode* champ, int ndx){
  if(champ ==NULL) champ= cur;
  if(cur ==NULL) return champ;
  if(cur->name=="Kinshasa") {
    std::cout<<"Kinshasa: "<< dist(vals, cur->vals, dim) <<std::endl;
    for(int i =0; i< dim; ++i) std::cout<< cur->vals[i] << " ";
  }
  double curdist = dist(vals, cur->vals, dim);
  double bestDist = dist(vals, champ->vals, dim); 
  if(curdist < bestDist) 
     champ = cur;
  
  bestDist = dist(vals, champ->vals, dim); 
  //champ = NN(vals, cur->left, champ, (ndx+1)%dim);
  //champ= NN(vals, cur->right, champ, (ndx+1)%dim);
  MegaNode *visit_first= cur->left, *visit_second= cur->right; 
  //if pt[ndx] is greater than splitting plane cur_>vals{ndx] go 
  //right else go left first
  if(vals[ndx] > cur->vals[ndx]) 
  { //std::swap(visit_first, visit_second); 
     visit_second=cur->left; visit_first= cur->right; 
  }
  champ= NN(vals, visit_first, champ, (ndx+1)%dim);
  bestDist = dist(vals, champ->vals, dim); 
  //if dist b/t pt[ndx] & plane is greater than bestDist this means
  //NN is already found... Dont search second subtree 
  if( fabs(vals[ndx] - cur->vals[ndx]) > bestDist)
    return champ;  
  champ= NN(vals, visit_second, champ, (ndx+1)%dim);

  return champ;
}


double MegaTree::dist( double vals[], double rhs[], int len){

  double dist =0.0; 
  for(int i=0; i < len; ++i)
    dist += pow(vals[i]- rhs[i], 2); 
  return sqrt(dist);
}
