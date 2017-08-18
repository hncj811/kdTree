#include "MegaTree.h" 
#include <string> 

int main(){

  int dimension=0; 
  std::string str;
  std::cout<< "Enter the file to be held in the tree.\n"; 
  std:: cin>> str; 
  std::cout << "Enter the number of the dimensions this data has.\n"; 
  std::cin >> dimension;  
  MegaTree tree(dimension, str); 

  tree.preorder(); 

  std::cout<< "Enter 3 integers from 0-255 and we will tell you the closest color:\n";

  double p[dimension]; 
  for(int i=0; i<dimension; i++) std::cin>>p[i];
  std::cout<<"\n"<< tree.nearestNode(p);
  return 0;
}
