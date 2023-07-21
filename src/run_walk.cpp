
#include "walk.hpp"

int main(int argc,char* argv[]){
  if(argc!=3){
    cerr<<"[run_walk] Argument error."<<endl;
    cout<<"argc is "<<argc<<endl;	
    exit(-1);
  }
  string filename=argv[1];
  int timeout=stoi(argv[2]);
  Stack stack;
  stack.from_file("todo/"+filename);
  Results results;
  results.clear();
  if(not walk(stack,results,timeout)){
    stack.split_to_file(filename);
  }
  results.to_file("results/"+filename);
  if(results.has_counter_example){
    cout<<"*******************"<<endl;
    cout<<"* Counter example *"<<endl;
    cout<<"*******************"<<endl;
    results.S_counter_example.display();
    results.S_counter_example.to_file(("counter/"+filename).c_str());
  }
  results.to_file(("results/"+filename).c_str());
  rename(("todo/"+filename).c_str(),("done/"+filename).c_str());
}
