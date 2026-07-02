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
    cout<<"Es tu turno, reino de "<<this->nom<<"."<<endl;
    data_prt();  
    //compra de tierra
    if(*td) {
        cout<<"Hay "<<*td<<" acres disponibles para comprar a "<<pt<<" bushels el acre."<<endl;
        short cmpr=0;
        while(!correcto) {
            cmpr=this->pregunta("Introduce el numero de acres que compraras/venderas");
            if(cmpr>0) {
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
            } else if(cmpr<0) {
                u2 venta=-cmpr;
                short res=this->vender(venta,pt);
                if(res==-1) cout<<"No puedes vender terreno que no tienes..."<<endl;
                else if(res==-2) cout<<"No puedes vender todo el terreno de tu ciudad..."<<endl;
                else {
                    cout<<"Vendes "<<venta<<" acres que te reportan un beneficio de "<<res<<" bushels."<<endl;
                    cout<<"Ahora tienes una extension de "<<this->ext<<" acres y "<<this->gra<<" bushels."<<endl;
                    correcto=true;
                }
            } else correcto=true;
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
            habs=pob_get();
            cout<<"La poblacion actual es de "<<habs<<" habitantes."<<endl;
        } else {
            cout<<"No tienes tanto grano..."<<endl;
        }
    }
    //desasignacion de trabajos
    this->hab_unset();
    u2 habs=pob_get();
    if(habs>0) {
        //asignacion de soldados
        cout<<"Asignacion de soldados a tu ciudad." << endl;
        cout<<"El numero maximo de soldados que puedes solicitar es " << this->sol_max() << "." << endl;
        cout<<"El precio por soldado es de " << PPS << " bushels." << endl;
        cout<<"Tienes "<<this->gra<<" bushels."<<endl;
        correcto=false;
        while(!correcto) {
            u2 sol=pregunta("Introduce el numero de soldados: ");
            short res=sol_set(sol);
            if(res==-1) cout<<"No tienes grano suficiente para pagar a los soldados"<<endl;
            else if(res==-2) cout<<"No tienes ese numero de soldados dispuestos a ser reclutados"<<endl;
            else {
                cout<<"El precio de esos soldados es de "<<sol*PPS<<" bushels."<<endl;
                cout<<"Te quedan "<<this->gra<<" bushels."<<endl;
                correcto=true;
            }
        }
        //asignacion de labradores
        u2 labmax=this->trb_max();
        cout<<"Asignacion de labradores a tu ciudad."<<endl;
        cout<<"Cada labrador se puede encargar de "<<APT<<" acres."<<endl;
        cout<<"Por cada "<<APB<<" acres necesitaras un bushel."<<endl;
        cout<<"Tienes disponibles "<<labmax<<" labradores."<<endl;
        cout<<"Tienes "<<this->gra<<" bushels y "<<this->ext<<" acres."<<endl;
        correcto=false;
        while(!correcto) {
            u2 acres=pregunta("Introduce el numero de acres que quieres labrar");
            if(acres>0) {
                short res=labrar(acres);
                if(res==-1) {
                    cout<<"No dispones de tantos trabajadores"<<endl;
                } else if(res==-2) {
                    cout<<"No dispones de tanto grano"<<endl;
                } else {
                    cout<<"PERFECTO! Empieza la recoleccion..."<<endl;
                    cout<<"Se ha obtenido "<<res<<" bushels este año."<<endl;
                    cout<<"Tienes "<<this->gra<<" bushels."<<endl;
                    correcto=true;
                }
            } else correcto=true;
        }
        //nacimientos
        u2 nac=this->reproducir();
        if(nac) {
            cout<<"Este año han habido "<<nac<<" nacimientos."<<endl;
        } else {
            cout<<"Este año no ha nacido nadie en tu ciudad"<<endl;
        }
        //eventos
        std::string res=this->evento();
        if(res.size()) {
            cout<<res<<endl;
        }
        //muertes
        u2 muer=this->morir();
        if(muer) {
            cout<<"Esta año han muerto "<<muer<<" habitantes de tu ciudad"<<endl;
            if(this->pob_get()==0) cout<<"Tu ciudad ha quedado completamente vacia..."<<endl;
        } else {
            cout<<"Este año no ha muerto nadie."<<endl;
        }
    }
}

std::vector<Persona> Humano::emigrar() {
    std::vector<Persona> em=this->Poblacion::emigrar();
    u2 ems=em.size();
    if(ems>0) {
        cout<<"Este año, por falta de trabajo o de alimento, "<<ems<<" habitantes emigran de tu ciudad."<<endl;
    }
    return em;
}

void Humano::inmigrar(std::vector<Persona> in) {
    u2 ins=Poblacion::inmigrar(in);
    if(ins>0) {
        cout<<"Este año, buscando una oportunidad, "<<ins<<" personas han venido a tu ciudad."<<endl;
    }
}

short Humano::derrota(u2 habini) {
    short dg=this->Poblacion::derrota();
    if(dg==0) {
        if(habini) {
            u2 habend=this->pob_get();
            int tpc=(habend-habini)*100/habini;
            if(tpc>0) {
                cout<<"La gente de tu ciudad esta contenta, has aumentado la poblacion en "<<tpc<<"%"<<endl;
            } else if(tpc==0) {
                cout<<"La eres indiferente a la gente. Tu poblacion se ha mantenido..."<<endl;
            } else {
                tpc=-tpc;
                cout<<"Tu poblacion ha descendido un "<<tpc<<"%"<<endl;
                if(tpc>CPJ) {
                    cout<<"La gente esta muy descontenta contigo. HAY UNA REVOLUCION EN LA CIUDAD Y TE DERROCAN"<<endl;
                    return -4;
                } else {
                    cout<<"La gente esta descontenta contigo"<<endl;
                }
            }
        } else cout<<"La gente quiere que sigas dirigiendo tu la ciudad..."<<endl;
    } else if(dg==-1) cout<<"TU CIUDAD HA DESAPARECIDO."<<endl;
    else if(dg==-2) cout<<"HAS PERDIDO TODOS LOS HABITANTES DE TU CIUDAD."<<endl;
    return dg;
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
