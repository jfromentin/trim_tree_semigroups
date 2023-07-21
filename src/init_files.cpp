#include "walk.hpp"

int main(){
  cout<<"****************************************"<<endl;
  cout<<"* Create files for ordinary semigroups *"<<endl;
  cout<<"****************************************"<<endl;
  Semigroup* O=new Semigroup;
  O->init_N();
  Semigroup* Onew=new Semigroup;
  int m=1;
  Results results;
  results.clear();
  do{
    if(trim(*O)) break;
    treat(*O,results);
    auto it=SonIterator(O);
    size_t irr_pos=0;
    it.move_next();
    Onew->son(*O,it.get_gen(),irr_pos++);
    while(it.move_next()){
      Semigroup S;
      S.son(*O,it.get_gen(),irr_pos++);
      if(not trim(S)){
	treat(S,results);
	if(S.g<g_max){
	  S.to_file("todo/"+to_string(S.m)+"_"+to_string(irr_pos));
	}
      }
    }
    swap(O,Onew);
  }while(O->g<=g_max);
  results.to_file("results/0");
      
}
