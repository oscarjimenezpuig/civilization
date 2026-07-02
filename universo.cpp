#include "universo.hpp"

Universo universo;

Universo::Universo(){
    //creacion de las ciudades
    u1 ishu=uniform(0,TCI-1);
    for(u1 k=0;k<TCI;k++) {
        if(ishu==k) this->ciucju=Humano(NOC[k],THA,TEX,TGR);
        else this->ciucor.push_back(Ordenador(NOC[k],THA,TEX,TGR));
    }
}

void Universo::migraciones() {
    u1 start=uniform(0,TCI-1); //pais que empieza en la reparticion
    u1 itera=0;
    while(this->pob.pob_get()>0 && itera<TCI) {
        u1 pais=(itera+start)%TCI;
        Poblacion* p=nullptr;
        if(pais==0) p=&(this->ciucju);
        else p=&(this->ciucor[itera-1]);
        u2 np=p->recibir();
        if(np>0) {
            //TODO Crear funcion que asigna np habitantes del universo al pais
        }
    }
}
        
    
            

    
