#include "humano.hpp"

using std::cout;
using std::endl;
using std::cin;

void Humano::data_prt() {
    cout<<"Poblacion: "<<this->pob_get()<<" habitantes"<<endl;
    cout<<"Extension: "<<this->ext<<" acres"<<endl;
    cout<<"Grano: "<<this->gra<<" bushels"<<endl;
}

short Humano::pregunta(std::string prg) {
    cout<<prg<<": ";
    short resp=0;
    cin>>resp;
    return resp;
}

Humano::Humano(std::string n,u2 hi,u2 ei,u2 gi):Poblacion(n,hi,ei,gi) {};


void Humano::actuar(u2* td,u2 pt) {
    bool correcto=false;
    cout<<"Bienvenido al año "<<this->year<<" de tu reinado en "<<this->nom<<endl;
    data_prt();  
    //compra de tierra
    if(*td) {
        cout<<"Hay "<<*td<<" acres disponibles para comprar a "<<pt<<" bushels el acre."<<endl;
        u2 cmpr=0;
        while(!correcto) {
            cmpr=this->pregunta("Introduce el numero de acres que compraras");
            if(cmpr<=*td) {
                u2 precio=cmpr*pt;
                if(precio<=this->gra) {
                    cout<<"Compras "<<cmpr<<" acres, pagando un total de "<<precio<<" bushels."<<endl;
                    this->gra-=precio;
                    this->ext+=cmpr;
                    *td-=cmpr;
                    correcto=true;
                } else cout<<"No tienes tanto grano..."<<endl;
            } else cout<<"No hay tanta tierra disponible..."<<endl;
        }
    }
    //asignacion de alimentos
    cout<<"Debes asignar el grano que servira de alimento a tus ciudadanos."<<endl;
    cout<<"Debes saber que cada individuo necesita "<< GPH << " bushels por año."<<endl;
    cout<<"Tienes "<<this->gra<<" bushels."<<endl;
    u2 gra=0;
    correcto=false;
    while(!correcto) {
        if(this->gra>0) {
            gra=this->pregunta("Introduce el grano asignado para comer");
        } else {
            cout<<"ATENCION: Te has quedado sin grano para dar de comer a tu poblacion..."<<endl;
        }
        u2 habs=pob_get();
        short res=this->alimentar(gra);
        correcto=(res>-1);
        if(res==habs) {
            cout<<"PERFECTO!! Has alimentado a toda la poblacion."<<endl;
        } else if(res<habs) {
            cout<<"Debido a la hambruna por el mal repartimiento de comida, han muerto "<<habs-res<<" habitantes."<<endl;
        } else {
            cout<<"No tienes tanto grano..."<<endl;
        }
    }
    //pasa año
    this->year++;
}

//prueba

using namespace std;

int main() {
    Humano h=Humano();
    u2 tdis=10;
    u2 ptie=20;
    for(u1 k=0;k<2;k++) {
        h.actuar(&tdis,ptie);
    }
    return 0;
}
