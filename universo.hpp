#include "ordenador.hpp"

constexpr short TCI=10; //numero de ciudades totales
constexpr short TEX=1000; //extension en acres de cada ciudad
constexpr short TGR=3000; //grano total de cada ciudad
constexpr short THA=100; //total de habitantes iniciales de cada ciudad
constexpr std::string NOC[]={"UR","URUK","ERIDU","LAGASH","NIPUR","KISH","BABILONIA","NINIVE","ASSUR","MARI"}; //nombre de ciudades babilonicas

class Universo {
    private:
        u2 year=1;
        Poblacion pob=Poblacion("Universo",THA,TEX,TGR); //poblacion del universo sin poblacion
        Humano ciucju; //
        std::vector<Ordenador> ciucor; //vector que contiene todas las ciudades dirigidas por el ordenador
    public:
        Universo(); //constructor del universo
        void actuar(); //actuacion de todas las ciudades activas
        void migraciones(); 
        //funcion que decide donde iran los habitantes residentes en el universo
        bool derrotas(); //evalua las derrotas de las ciudades, devolvera false
                         //en el momento que el jugador caiga derrotado
};

extern Universo universo;

