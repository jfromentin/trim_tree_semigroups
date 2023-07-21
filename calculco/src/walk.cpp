#include "walk.hpp"

bool walk(Stack& stack,Results &results,int timeout){
  const auto start = time(nullptr);
  size_t numbers=0;
  Semigroup* father=new Semigroup;
  while(not stack.is_empty()){
    ++numbers;
    if(numbers%10000000==0){
      const auto now=time(nullptr);
      auto duration=now-start;
      if(duration>timeout){
	delete father;
	return false;
      }
    }
    stack.pop(&father);
    auto it=SonIterator(father);
    size_t irr_pos=0;
    size_t g=father->g;
    if(g<g_max-1){
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
  return true;
}
