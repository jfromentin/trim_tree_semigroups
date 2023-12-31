#ifndef SEMIGROUP_HPP
#define SEMIGROUP_HPP


#include <cstring>
#include <cstdint>
#include <cassert>
#include <immintrin.h>
#include <x86intrin.h>
#include <fstream>

#include "config.hpp"
#include "sse.hpp"

static const v16u masks[16]={
  v16u_new(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0XFF),
  v16u_new(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0XFF)
};

static const v16u shuffles[16]={
  v16u_new(0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF),
  v16u_new(0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE),
  v16u_new(0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD),
  v16u_new(0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC),
  v16u_new(0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB),
  v16u_new(0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA),
  v16u_new(0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9),
  v16u_new(0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8),
  v16u_new(0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7),
  v16u_new(0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6),
  v16u_new(0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5),
  v16u_new(0x5,0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4),
  v16u_new(0x4,0x5,0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3),
  v16u_new(0x3,0x4,0x5,0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2),
  v16u_new(0x2,0x3,0x4,0x5,0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1),
  v16u_new(0x1,0x2,0x3,0x4,0x5,0x6,0x7,0X8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0)
};

static const v16u right_ones_array[16]={
  v16u_new(0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1),
  v16u_new(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1)
};
 
class Semigroup{
public:
  static const size_t _size=3*(g_max-1);
  static const size_t nsse=((_size+15)/16);
  static const size_t size=16*nsse;
  union{
    v16u delta_sse[nsse];
    u8 delta[size];
  }__attribute__((aligned(16)));
  size_t c,m,g,e,e_left,left;
  Semigroup();
  void init_N();
  void copy_delta(const Semigroup& S);
  void son(const Semigroup& S,size_t x,size_t pos);
  void display() const;
  void to_file(string filename) const;
  void from_file(string filename);
  void to_file(fstream& file) const;
  void from_file(fstream& file);
};

class SonIterator{
public:
  const Semigroup *S;
  size_t iblock, gen, bound;
  int mask;
public:
  SonIterator(const Semigroup *S);
  bool move_next();
  uint8_t count();
  inline size_t get_gen() const {return gen;};
};

inline SonIterator::SonIterator(const Semigroup* _S):S(_S),bound(min(Semigroup::nsse-1,(_S->c+_S->m+15)>>4)){
  iblock=(S->c>>4);
  size_t imask=(S->c&0xF);
  v16u a=masks[imask]&S->delta_sse[iblock];
  mask=move_mask(cmp_eq(a,v16u_one));
  gen=(iblock<<4)-1;
};

inline bool
SonIterator::move_next(){
  while(not mask){
    ++iblock;
    if(iblock>bound) return false;
    gen=(iblock<<4)-1;
    mask=move_mask(cmp_eq(S->delta_sse[iblock],v16u_one));
  }
  int shift=__bsfd(mask)+1;
  gen+=shift;
  mask>>=shift;
  return true;
};

inline
Semigroup::Semigroup(){
}

inline void
Semigroup::from_file(string filename){
   fstream file;
   file.open(filename.c_str(),ios::in|ios::binary);
   from_file(file);
   file.close();
}

inline void
Semigroup::to_file(string filename) const{
   fstream file;
   file.open(filename.c_str(),ios::out|ios::binary|ios::trunc);
   to_file(file);
   file.close();
}
#endif
