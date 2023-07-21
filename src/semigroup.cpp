#include "semigroup.hpp"

void
Semigroup::init_N(){
  c=1;
  g=0;
  m=1;
  e=1;
  e_left=0;
  left=1;
  for(size_t x=0;x<size;++x){
    delta[x]=1+x/2;
  }
}

void
Semigroup::son(const Semigroup& S,size_t x,size_t pos){
  //cout<<"======= son ========"<<endl;
  c=x+1;
  g=S.g+1;
  int e_delta;
  if(x>S.m){
    m=S.m;
    e_delta=(S.delta[x+S.m]==2)?0:-1;
  }
  else{
    m=S.m+1;
    e_delta=1;
  }
  e=S.e+e_delta;
  e_left=S.e_left+pos;
  left=S.left+x-S.c;

  memcpy(delta,S.delta,size);
 
  size_t ix=x/16;
  size_t sx=x%16; //delta_sse[ix]=[...,d(x),...]

  v16u shuffle_mask=shuffles[sx]; 
  v16u right_ones=right_ones_array[sx];
  v16u left_ones=v16u_one-right_ones;
  v16u u=v16u_zero;
  const v16u* pz=&S.delta_sse[0];
  for(size_t iy=ix;iy<nsse;++iy){
    v16u bz=cmp_gt(*pz,v16u_zero);//[c(0),...,c(sx),c(sx+1)...,c(15)] where c(t)=(d(t)>=1?0xFF:0x00))
    bz=shuffle(bz,shuffle_mask);//[...,c(15),c(0)@sx,...,]
    u|=(bz&right_ones);//[u(0),...,u(sx-1),o(0)@sx,...,o(sx)] where o(t)=(d(t)>=1?0x1:0x0)
    delta_sse[iy]-=u;
    u=bz&left_ones;//[...,o(15),0@sx,...]
    ++pz;       
  }
}

void
Semigroup::display() const{
  bool flag=false;
  cout<<'<';
  for(size_t x=1;x<size;++x){
    if(delta[x]==1){
      if(flag) cout<<',';
      flag=true;
      cout<<x;
    }
  }
  cout<<"> m = "<<m<<" g = "<<g<<" c = "<<c<<" e = "<<e<<" left = "<<left<<endl;
  return;
  for(size_t x=0;x<40;++x){
    if(x<10) cout<<' ';
    cout<<(int)x<<'|';
  }
  cout<<endl;
  for(size_t x=0;x<40;++x){
    cout<<"--|";
  }
  cout<<endl;
  for(size_t x=0;x<40;++x){
    if(delta[x]<10) cout<<' ';
    cout<<(int)delta[x]<<'|';
  }
  cout<<endl;
}

void
Semigroup::to_file(fstream& file) const{
  file.write((char*)delta,size);
  file.write((char*)&c,sizeof(size_t));
  file.write((char*)&m,sizeof(size_t));
  file.write((char*)&g,sizeof(size_t));
  file.write((char*)&e,sizeof(size_t));
  file.write((char*)&e_left,sizeof(size_t));
  file.write((char*)&left,sizeof(size_t));
}
			 
void
Semigroup::from_file(fstream& file){
  file.read((char*)delta,size);
  file.read((char*)&c,sizeof(size_t));
  file.read((char*)&m,sizeof(size_t));
  file.read((char*)&g,sizeof(size_t));
  file.read((char*)&e,sizeof(size_t));
  file.read((char*)&e_left,sizeof(size_t));
  file.read((char*)&left,sizeof(size_t));
}
			 
