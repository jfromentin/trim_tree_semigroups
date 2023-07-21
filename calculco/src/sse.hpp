#ifndef SSE_VEC16_HPP
#define SSE_VEC16_HPP

#include <tmmintrin.h>
#include <cstdint>
#include <iostream>
#include "hex.hpp"

using namespace std;

using u8=uint8_t;

union v16u{
  __m128i sse;
  u8 v[16];
} __attribute__((aligned(16)));

typedef union v16u v16u;

v16u v16u_new(u8 a);
v16u v16u_new(u8 a0,u8 a1,u8 a2,u8 a3,u8 a4,u8 a5,u8 a6,u8 a7,u8 a8,u8 a9,u8 a10,u8 a11,u8 a12,u8 a13,u8 a14,u8 a15);

v16u operator&(const v16u& u,const v16u& v);
void operator|=(v16u& u,const v16u& v);
void operator-=(v16u& u,const v16u& v);
v16u operator-(const v16u& u,const v16u& v); 
v16u cmp_eq(const v16u& u,const v16u& v);
v16u cmp_gt(const v16u& u,const v16u& v);
v16u shuffle(const v16u& u,const v16u& v);

int move_mask(const v16u& u);

ostream& operator<<(ostream& os,const v16u& u);

static const v16u v16u_zero=v16u_new(0);
static const v16u v16u_one=v16u_new(1);

inline v16u
operator&(const v16u& u,const v16u& v){
  v16u w;
  w.sse=_mm_and_si128(u.sse,v.sse);
  return w;
}

inline void
operator|=(v16u& u,const v16u& v){
  u.sse=_mm_or_si128(u.sse,v.sse);
}

inline void
operator-=(v16u& u,const v16u& v){
  u.sse=_mm_sub_epi8(u.sse,v.sse);
}

inline v16u
operator-(const v16u& u,const v16u& v){
  v16u w;
  w.sse=_mm_sub_epi8(u.sse,v.sse);
  return w;
}

inline v16u
cmp_eq(const v16u& u,const v16u& v){
  v16u w;
  w.sse=_mm_cmpeq_epi8(u.sse,v.sse);
  return w;
}

inline v16u
cmp_gt(const v16u& u,const v16u& v){
  v16u w;
  w.sse=_mm_cmpgt_epi8(u.sse,v.sse);
  return w;
}

inline v16u
shuffle(const v16u& u,const v16u& v){
  v16u w;
  w.sse=_mm_shuffle_epi8(u.sse,v.sse);
  return w;
}

inline int
move_mask(const v16u& u){
  return _mm_movemask_epi8(u.sse);
}
#endif
