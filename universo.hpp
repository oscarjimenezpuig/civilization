#include "ordenador.hpp"

constexpr short TCI=10; //numero de ciudades totales
constexpr short TEX=1000; //extension en acres de cada ciudad
constexpr short TGR=3000; //grano total de cada ciudad
constexpr short THA=100; //total de habitantes iniciales de cada ciudad
constexpr std::string NOC[]={"UR","URUK","ERIDU","LAGASH","NIPUR","KISH","BABILONIA","NINIVE","ASSUR","MARI"}; //nombre de ciudades babilonicas

class Universo {
    private: 
        u2 gra; //grano disponible para pagar ventas
        u2 ext; //extension sin propietario disponible en el universo
        u2 hab; //habitantes sin ciudad en el universo
        Humano ciucju; //
        std::vector<Ordenador> ciucor; //vector que contiene todas las ciudades dirigidas por el ordenador
    public:
        Universo(); //constructor del universo
};

extern Universo universo;

