#ifndef STACK_HPP
#define STACK_HPP

#include "semigroup.hpp"

class Stack{
public:
  static const size_t capacity=g_max*(g_max+1)/2;
  size_t size;
  Semigroup** data;
  Stack();
  void pop(Semigroup** S);
  void push();
  Semigroup* next();
  bool is_empty();
  void display();
  ~Stack();
  void from_file(string filename);
  void split_to_file(string filename) const;
};

inline void
Stack::push(){
  size++;
}

inline Semigroup*
Stack::next(){
  return data[size];
}


inline void
Stack::pop(Semigroup** S){
  swap(*S,data[--size]);
}

inline bool
Stack::is_empty(){
  return size==0;
}



#endif
