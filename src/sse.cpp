#include "sse.hpp"

v16u v16u_new(uint8_t a){
  v16u u;
  u.sse=_mm_set1_epi8(a);
  return u;
}

v16u v16u_new(u8 a0,u8 a1,u8 a2,u8 a3,u8 a4,u8 a5,u8 a6,u8 a7,u8 a8,u8 a9,u8 a10,u8 a11,u8 a12,u8 a13,u8 a14,u8 a15){
  v16u u;
  u.v[0]=a0;
  u.v[1]=a1;
  u.v[2]=a2;
  u.v[3]=a3;
  u.v[4]=a4;
  u.v[5]=a5;
  u.v[6]=a6;
  u.v[7]=a7;
  u.v[8]=a8;
  u.v[9]=a9;
  u.v[10]=a10;
  u.v[11]=a11;
  u.v[12]=a12;
  u.v[13]=a13;
  u.v[14]=a14;
  u.v[15]=a15;
  return u;
}

ostream& operator<<(ostream& os,const v16u& u){
  os<<'[';
  disp_hex(os,u.v[0]);
  for(size_t i=1;i<16;++i){
    os<<' ';
    disp_hex(os,u.v[i]);
  }
  return os<<']';

}
