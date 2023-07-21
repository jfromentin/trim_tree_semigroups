#include "walk.hpp"


int main(){
  cout<<"g_max = "<<g_max<<endl;
  Semigroup N;
  Results results;
  results.clear();
  Stack stack;
  stack.next()->init_N();
  stack.push();
  walk(stack,results,1000000);
  for(size_t g=0;g<=g_max;++g){
    cout<<g<<"\t"<<results.ng[g]<<endl;
  }


}
