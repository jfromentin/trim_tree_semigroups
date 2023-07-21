#include "results.hpp"

int main(int argc,char* argv[]){
  if(argc!=2){
    cerr<<"[show_res] Argument error"<<endl;
    exit(-1);
  }
  Results results;
  string filename=argv[1];
  results.from_file(("results/"+filename).c_str());

  for(size_t g=0;g<=g_max;++g){
    cout<<g<<"\t"<<results.ng[g]<<endl;
  }
  exit(0);
}
