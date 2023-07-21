#include "stack.hpp"

Stack::Stack(){
  data=new Semigroup*[capacity];
  for(size_t i=0;i<capacity;++i){
    data[i]=new Semigroup;
  }
  size=0;
}


Stack::~Stack(){
  for(size_t i=0;i<capacity;++i){
    delete data[i];
  }
  delete[] data;
}

void
Stack::display(){
  cout<<"---- Stack -----"<<endl;
  for(size_t i=0;i<size;++i){
    cout<<i<<"\t"<<data[i]<<endl;
  }
  cout<<"next \t"<<data[size]<<endl;
  cout<<"----------------"<<endl;
}

void
Stack::from_file(string filename){
  fstream file;
  file.open(filename.c_str(),ios::in|ios::binary);
  while(!file.eof()){
    next()->from_file(file);
    push();
  }
  file.close();
}

void
Stack::split_to_file(string filename) const{
  string filename1="next/"+filename+"_0";
  string filename2="next/"+filename+"_1";
  fstream file[2];
  file[0].open(filename1.c_str(),ios::out|ios::binary|ios::trunc);
  file[1].open(filename2.c_str(),ios::out|ios::binary|ios::trunc);
  for(size_t i=0;i<size;++i){
    data[i]->to_file(file[i%2]);
  }
  file[0].close();
  file[1].close();
}
