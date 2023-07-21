#ifndef TRIM_HPP
#define TRIM_HPP

static const size_t k=4;

inline bool
trim_wilf1(Semigroup& S){

  return k*S.e_left>=S.m;
}

inline bool
trim_wilf2(Semigroup& S){
  return (k*S.e)>=S.m+k*(g_max-S.g);
}

inline bool
trim_wilf3(Semigroup& S){
	size_t c=S.c;
size_t m=S.m;
	size_t i=(m-1)-c%m;
	return S.delta[c+i]!=1;
}

inline bool
trim(Semigroup& S){
  return trim_wilf1(S) or trim_wilf2(S) or trim_wilf3(S);
}

#endif
