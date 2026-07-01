#include "humano.hpp"

class Ordenador:public Poblacion {
    private:
    public:
        Ordenador(std::string nombre,u2 hab_ini,u2 ext_ini,u2 gra_ini);
        void actuar(u2* tierra_disponible,u2 precio_tierra);
};
