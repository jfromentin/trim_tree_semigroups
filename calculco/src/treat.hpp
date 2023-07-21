#ifndef TREAT_HPP
#define TREAT_HPP

#include "results.hpp"

void treat(const Semigroup& S,Results &results);

inline
void treat(const Semigroup& S,Results &results){
  int wilf=S.e*S.left-S.c;
  if(wilf<0 and not results.has_counter_example){
    results.has_counter_example=true;
    results.S_counter_example=S;
  }
  results.ng[S.g]++;
}


#endif
