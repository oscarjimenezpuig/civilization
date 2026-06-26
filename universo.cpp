#include "universo.hpp"

Universo universo;

Universo::Universo(){
    //establecimiento de variables
    this->gra=TGR;
    this->ext=TEX;
    this->hab=THA;
    //creacion de las ciudades
    u1 ishu=uniform(0,TCI-1);
    for(u1 k=0;k<TCI;k++) {
        if(ishu==k) this->ciucju=Humano(NOC[k],THA,TEX,TGR);
        else this->ciucor.push_back(Ordenador(NOC[k],THA,TEX,TGR));
    }
}
            

    
