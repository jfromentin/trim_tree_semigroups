#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <iostream>
#include "semigroup.hpp"


using namespace std;

class Results{
public:
  size_t ng[g_max+1];
  bool has_counter_example;
  Semigroup S_counter_example;
  void clear();
  void add(const Results& res);
  void to_file(string filename) const;
  void from_file(string filename);
};


inline
void Results::clear(){
  has_counter_example=false;
  for(size_t g=0;g<=g_max;++g){
    ng[g]=0;
  }
}

inline
void Results::add(const Results& res){
  if((not has_counter_example) and res.has_counter_example){
    S_counter_example=res.S_counter_example;
  }
  for(size_t g=0;g<=g_max;++g){
    ng[g]+=res.ng[g];
  }
}

inline
void Results::to_file(string filename) const{
  fstream file;
  file.open((filename).c_str(),ios::out|ios::binary|ios::trunc);
  file.write((char*)ng,sizeof(size_t)*(g_max+1));
  file.close();
}


inline
void Results::from_file(string filename){
  fstream file;
  file.open((filename).c_str(),ios::in|ios::binary);
  file.read((char*)ng,sizeof(size_t)*(g_max+1));
  file.close();
}
#endif
