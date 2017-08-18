#include "MegaTree.h" 

int main( )
{ 
  MegaTree tree(2); 
  std::cout<<"This program allows you to make a 2d tree.\n";
  char quit= 'f'; 
  double p[2];
  double a, b; 
  while( quit != 'q'){
    std::cout<<"Enter 2 doubles.\n"; 
    std::cin>> a >>b; 
    p[0]= a; p[1]= b; 
    tree.insert(" ", p); 
    std::cout<< "Enter the letter q to quit.\nEnter any other letter to continue.\n";
    std::cin>> quit; 

  }
  tree.preorder();
  return 0; 
}
