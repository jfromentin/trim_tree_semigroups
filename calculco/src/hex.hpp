#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <cstdint>

using namespace std;

static const char hex_char[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void disp_hex(ostream& os,uint8_t i);

inline void
disp_hex(ostream& os,uint8_t i){
  os<<hex_char[i>>4]<<hex_char[i&0xF];
}

#endif
