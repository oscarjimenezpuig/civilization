#include "poblacion.hpp"

//PERSONA

using Vptr = std::vector<Persona>::iterator;

inline bool isin(double val,double min,double max) {
    //dice si un valor esta en el intervalo
    return (val>=min && val<=max);
}

inline bool canemp(Persona p) {
    //condiciones para que una persona pueda emparejarse
    constexpr int EMIN=15;
    constexpr int EMAX=45;
    return (!p.is_nul() && p.gen!=0 && isin(p.eda,EMIN,EMAX) && p.emp==0);
}

inline bool cantrb(Persona p) {
    //condiciones para que una persona pueda trabajar
    constexpr int EMIN=15;
    constexpr int EMAX=65;
    return (!p.is_nul() && !p.trb && !p.sol && isin(p.eda,EMIN,EMAX) && p.gen!=255 && p.gen!=0);
}

inline bool cansol(Persona p) {
    //condiciones para que una persona pueda trabajar
    constexpr int EMIN=20;
    constexpr int EMAX=40;
    return (!p.is_nul() && !p.trb && !p.sol && p.gen>0 && (isin(p.eda,EMIN,EMAX) || p.gen==255));
}

inline bool canrep() {
    constexpr int PTH=10;
    return (uniform(0,99)<PTH)?true:false;
}

Persona::Persona(u1 g,u1 e) {
    this->eda=e;
    do {
        u2 prev=normal(40,15);
        if(g==0) this->edm=prev/2;
        else if(g==255) this->edm=prev*2;
        else this->edm=prev;
    } while(this->edm<=this->eda);
    this->sex=int(uniform(0,2));
    this->emp=this->sol=this->trb=this->inf=0;
    this->gen=g;
}

void Persona::crece() {
    if(this->edm) ++this->eda;
}

Persona Persona::empareja(std::vector<Persona> ps) {
    if(canemp(*this)) {
        Vptr it=ps.begin();
        while(it!=ps.end()) {
            if(canemp(*it) && this->sex != it->sex) {
                this->emp=it->emp=1;
                return *it;
            }
            it++;
        }
    }
    return PERNUL;
}

Persona Persona::reproduce(Persona p) {
    Persona np=PERNUL;
    if(canrep() && !p.is_nul()) np=Persona(this->gen ^ p.gen);
    return np;
}

bool Persona::muere() {
    if(!this->is_nul() && (this->eda==this->edm || this->inf)) {
        *this=PERNUL;
        return true;
    }
    return false;
}

bool Persona::is_nul() {
    return (this->edm==0);
}

void Persona::info() {
    if(!this->is_nul()) {
        std::cout<<"Edad: "<<(int)this->eda<<"("<<(int)this->edm<<")";
        std::cout<<" Sexo: "<<(int)this->sex<<" Genoma: "<<(int)this->gen;
        std::cout<<" ESTI: "<<(int)this->emp<<(int)this->sol<<(int)this->trb<<(int)this->inf<<std::endl;
    }
}

//POBLACION

inline bool Poblacion::pobins(Persona pp) {
    if(!pp.is_nul()) {
        Vptr it=this->pob.begin();
        while(it!=this->pob.end()) {
            if(it->edm==0) {
                *it=pp;
                return true;
            }
            it++;
        }
        this->pob.push_back(pp);
        return true;
    }
    return false;
}           

Poblacion::Poblacion(std::string n,u2 hi,u2 ei,u2 gi) {
    this->nom=n;
    for(int k=0;k<hi;k++) this->pob.push_back(Persona(uniform(0,255),uniform(20,40)));
    this->ext=ei;
    this->gra=gi;
}

u2 Poblacion::pob_get() {
    u2 habitants=0;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        if(!it->is_nul()) ++habitants;
        it++;
    }
    return habitants;
}

u2 Poblacion::ext_get() {
    return this->ext;
}

u2 Poblacion::gra_get() {
    return this->gra;
}

u2 Poblacion::trb_max() {
    u2 trb=0;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        if(cantrb(*it)) trb++;
        it++;
    }
    return trb;
}

u2 Poblacion::sol_max() {
    u2 sol=0;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        if(cansol(*it)) sol++;
        it++;
    }
    return sol;
}

bool Poblacion::trb_set(u2 trb) {
    if(trb<=this->trb_max()) {
        Vptr it=this->pob.begin();
        while(it!=this->pob.end() && trb) {
            if(cantrb(*it)) {
                it->trb=1;
                trb--;
            }
            it++;
        }
        return true;
    }
    return false;
} 

short Poblacion::sol_set(u2 sol) {
    u2 precio=sol*PPS;
    if(precio<=this->gra) {
        if(sol<=this->sol_max()) {
            Vptr it=this->pob.begin();
            while(it!=this->pob.end() && sol) {
                if(!it->sol && it->gen==255) {
                    sol--;
                    it->sol=1;
                }
                it++;
            }
            it=this->pob.begin();
            while(it!=this->pob.end() && sol) {
                if(cansol(*it)) {
                    it->sol=1;
                    sol--;
                }
                it++;
            }
            this->gra-=precio;
            return sol;
        } else return -2;
    }
    return -1;
} 

void Poblacion::hab_unset() {
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        it->sol=it->trb=0;
        it++;
    }
}

short Poblacion::alimentar(u2 gra) {
    short alimentados=-1;
    if(gra<=this->gra) {
        alimentados=0;
        this->gra-=gra;
        Vptr it=this->pob.begin();
        while(it!=this->pob.end() && gra>=GPH) {
            gra-=GPH;
            ++alimentados;
            it++;
        }
        while(it!=this->pob.end()) {
            *it=PERNUL;
            it++;
        }
    }
    return alimentados;
}

void Poblacion::crecer() {
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        it->crece();
        it++;
    }
}

u2 Poblacion::reproducir() {
    u1 nacimientos=0;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) it++->emp=0;
    it=this->pob.begin();
    while(it!=this->pob.end()) {
        Persona p=it->empareja(this->pob);
        if(!p.is_nul()) {
            Persona h=it->reproduce(p);
            if(this->pobins(h)) ++nacimientos;
        }
        it++;
    }
    return nacimientos;
}

u2 Poblacion::morir() {
    u1 muertes=0;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        if(it->muere()) {
            ++muertes;
        }
        it++;
    }
    return muertes;
}

short Poblacion::comprar(u2 c,u2 d,u2 p) {
    if(c<=d) {
        u2 pt=p*c;
        if(this->gra<=pt) {
            this->gra-=pt;
            this->ext+=c;
            return 0;
        } else return -2;
    } else return -1;
}

short Poblacion::vender(u2 v,u2 p) {
    short beneficio=0;
    if(v<this->ext) {
        beneficio=v*p;
        this->gra+=beneficio;
        this->ext-=v;
    } else if(v==this->ext) beneficio=-2;
    else beneficio=-1;
    return beneficio;
}

short Poblacion::labrar(u2 a) {
        u2 t=a/APT;
        u2 g=a/APB;
        if(t<=this->trb_max()) {
        if(g<=this->gra) {
            trb_set(t);
            this->gra-=g;
            u2 ept=APT*t;
            u2 epg=APB*g;
            u2 ext=(ept<epg)?ept:epg;
            short grano=0;
            for(int k=0;k<ext;k++) grano+=uniform(MIP,MAP);
            this->gra+=grano;
            return grano;
        } else return -2;
    } else return -1;
}

std::string Poblacion::evento() {
    std::ostringstream oss;
    if(uniform(0,99)<PEP) {
        oss<<"La enfermedad ha atacado a tu ciudad.";
        Vptr it=this->pob.begin();
        while(it!=this->pob.end()) {
            if(!it->is_nul() && ((it->gen==0)||(it->gen<255 && uniform(0,99)<PIN))) it->inf=1;
            it++;
        }
    }else if(uniform(0,99)<PER) {
        int losed=this->gra*uniform(TMI,TMA)/100;
        if(losed>0) {
            oss<<"Las ratas visitan tu ciudad y han devorado "<<losed<<" bushels de grano.";
            this->gra-=losed;
        }
    }
    std::string res=oss.str();
    return res;
}           

void Poblacion::info() {
    std::cout<<this->nom<<std::endl;
    u2 habs=this->pob_get();
    std::cout<<"P: "<<habs<<" G: "<<this->gra<<" E: "<<this->ext<<std::endl;
    Vptr it=this->pob.begin();
    while(it!=this->pob.end()) {
        it->info();
        it++;
    }
}





