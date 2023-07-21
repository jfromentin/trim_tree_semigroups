#include "semigroup.hpp"

int main(int argc,char* argv[]){
  string filename=argv[1];
  Semigroup S;
  S.from_file(filename);
  S.display();
}

