#include "humano.hpp"

constexpr short TCI=10 //numero de ciudades totales
constexpr short TEX=1000*TCI //extension en acres total del universo
constexpr short TGR=3000*TCI //grano total en el universo
constexpr short THA=100*TCI //total de habitantes iniciales en el universo

class Universo {
    private: 
        u2 gra; //grano disponible para pagar ventas
        u2 ext; //extension sin propietario disponible en el universo
        u2 hab; //habitantes sin ciudad en el universo
    public:

