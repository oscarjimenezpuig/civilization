#include "general.hpp"

class Persona {
    private:
        struct {
            u1 eda : 7; //edad actual
            u1 edm : 7; //edad maxima
            u1 emp : 1; //emparejado
            u1 sex : 1; //sexo
        };
        u1 gen;
    public:
        Persona(u1 eda=0,u1 genoma=-1); //define una persona
        s1 empareja(vector<Persona>::iterator ppersona); //empareja a una persona con p
        bool muere(); //comprueba si la persona muere
        void evolucion(); //suma un año a la persona
};


