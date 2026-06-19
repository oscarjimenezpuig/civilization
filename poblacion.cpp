#include "poblacion.hpp"

Persona::Persona(u1 g,u1 e) {
    this->eda=e;
    do {
        this->edm=normal(40,15);
    } while(this->edm<=this->eda);
    this->sex=int(uniform(0,2));
    this->emp=0;
    this->gen=g;
}

void Persona::info() {
    std::cout<<"Edad: "<<(int)this->eda<<"("<<(int)this->edm<<") Sexo: "<<(int)this->sex<<" Emparejado: "<<(int)this->emp<<" Genoma: "<<(int)this->gen<<std::endl;
}


//prueba

using namespace std;

int main() {
    for(int k=0;k<20;k++) {
        Persona p=Persona(uniform(0,256),uniform(20,40));
        p.info();
    }
    return 0;
}
