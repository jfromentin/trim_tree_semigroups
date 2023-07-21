#include "walk.hpp"

void walk(Stack& stack,Results &results,size_t g_limit){
  Semigroup* father=new Semigroup;
  while(not stack.is_empty()){
    stack.pop(&father);
    auto it=SonIterator(father);
    size_t irr_pos=0;
    size_t g=father->g;
    if(g<g_limit-1){
      while(it.move_next()){
	Semigroup* son=stack.next();
	son->son(*father,it.get_gen(),irr_pos++);
	if(not trim(*son)){
	  stack.push();
	  treat(*son,results);
	}
      }
    }
    else{
      while(it.move_next()){
	Semigroup* son=stack.next();
	son->son(*father,it.get_gen(),irr_pos++);
	if(not trim(*son)){
	  treat(*son,results);
	}
		
      }
    }     
  }
  delete father;
}
