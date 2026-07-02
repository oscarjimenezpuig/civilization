#include "poblacion.hpp"

//Este archivo contiene la clase jugador, heredera de Poblacion para la
//gestion de una poblacion por un jugador humano

constexpr short CPJ=40; //tanto porciento limite para perder

class Humano : public Poblacion {
    private: 
        void data_prt(); //imprime los datos
        short pregunta(std::string prg); //hace una pregunta
    public:
        Humano(std::string nombre="Babylon",u2 hab_ini=100,u2 ext_ini=1000,u2 gra_ini=3000);
        //construcctor
        void actuar(u2* tierra_disponible,u2 precio_tierra);
        //evolucion de un turno
        std::vector<Persona> emigrar();
        //emigran personas de la ciudad del humano
        void inmigrar(std::vector<Persona> ps);
        //el conjunto de personas que viene a la ciudad.
        short derrota(u2 habini=0);
        //examina si hay derrota en el caso humano
        //0: no hay derrota
        //-1: no hay tierra
        //-2: no hay poblacion
        //-3: la poblacion ha descendido mas del maximo permitido
};


