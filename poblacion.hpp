#include "general.hpp"

//REGLAS
//Emparejamiento de 15 a 45 años
//Probabilidad de nacimiento 10
//Trabajadores posibles desde los 15 a los 65, no puede ser heroe
//Soldados des de los 20 a los 40 o los heroes siempre
//El precio de un acre oscila entre los 16 y los 27 bushels
//Un trabajador labra 10 acres un bushel sirve para 2 acres
//Produccion de acre oscila entre 0 y 6 bushels
//Probabilidad de que suceda el evento plaga 15%, hay una probabilidad del 50% que un poblador se vea afectado
//La plaga nunca afecta a los heroes pero mata directo a deficientes
//Probabilidad de eventos ratas, 40% de probabilidad entre el 25% y el total de grano
//Cada individuo necesita 20 bushels para alimentarse por año

constexpr u2 APT=10; //acres que labra un trabajador
constexpr u2 APB=2; //acres con los que labras un bushel
constexpr u1 MAP=6; //maxima produccion por acre
constexpr u1 MIP=0; //minima produccion por acre
constexpr int PER=40; //probabilidad evento ratas
constexpr int PEP=15; //probabilidad evento plaga
constexpr int PIN=50; //probabilidad de caer enfermo
constexpr int TMI=25; //tanto por ciento minimo de perdida por ratas
constexpr int TMA=100; //tanto por ciento maximo de perdida por ratasç
constexpr u2 GPH=20; //cantidad de grano necesario por habitante
constexpr u2 PPS=10; //bushels extra que cobra un soldado

class Persona {
    public:
        struct {
            u1 emp : 1; //emparejado
            u1 sol : 1; //soldado
            u1 trb : 1; //trabajador
            u1 sex : 1; //sexo
            u1 inf : 1; //mira si tiene alguna infeccion (y por tanto muere en la verificacion muerte)
        };
        u1 eda=0;
        u1 edm=0;
        u1 gen=0;
        constexpr Persona() : emp(0),sol(0),trb(0),sex(0),inf(0),eda(0),edm(0),gen(0) {}; //constructor por defecto
        Persona (u1 genoma,u1 edad=0); //se crea una persona no nula 
        void crece(); //suma un año a la persona
        Persona empareja(std::vector<Persona> personas); //se empareja
        Persona reproduce(Persona p); //mira si tiene un hijo con la persona p
        bool muere(); //checkea si muere de muerte natural
        bool is_nul(); //dice si la persona es nula
        void info();
};

constexpr Persona PERNUL=Persona(); //Persona nula

class Poblacion {
    protected:
        std::string nom;
        u2 ext; //extension en acres
        u2 gra; //grano en bushels
        std::vector<Persona> pob; //personas que componen la poblacion
        bool pobins(Persona p); //inserta una nueva persona en la poblacion
    public:
        Poblacion(std::string nombre,u2 hab_ini=2,u2 ext_ini=20,u2 gra_ini=60); //constructor
        u2 pob_get(); //numero de habitantes
        u2 ext_get(); //extension
        u2 gra_get(); //grano
        u2 trb_max(); //numero maximo de personas que pueden ser trabajadores
        u2 sol_max(); //numero maximo de personas que pueden ser soldado
        bool trb_set(u2 trb); //establecer el numero de trabajadores de la ciudad
        short sol_set(u2 sol); 
        //establecer el numero de soldados de la ciudad
        //>=0: numero de soldados contratados
        //-1: El precio de los soldados excede del grano
        //-2: Hay mas soldados solicitados que los que hay
        void hab_unset();//quita la profesion a todos los habitantes
        short alimentar(u2 gra); 
        //alimentamos a la poblacion con una cierta cantidad de grano
        //>=0 numero de habitantes alimentados
        //-1: El grano dado excede a la poblacion
        void crecer(); //hace crecer a la poblacion (envejecer un año)
        u2 reproducir(); //empareja y reproduce a la poblacion dando el numero de nacimientos
        u2 morir(); //hace morir a la poblacion, dando el numero de muertes
        short comprar(u2 compra,u2 disponibles,u2 precio); 
        //compra una serie de acres de unos disponibles a un precio concreto
        //0: correcto
        //-1: no hay tantos disponibles
        //-2: no tienes grano suficiente para comprar
        short vender(u2 venta,u2 precio);
        //venta de una serie de acres
        //>=0: correcto, devuelve ganancia
        //-1: no dispones de tantos acres
        //-2: no puedes vender todos los acres
        short labrar(u2 acres);
        //>0: produccion de grano
        //-1: no dispones de tantos trabajadores
        //-2: no dispones de tanto grano
        std::string evento();
        //eventos que afectan a una poblacion, se devuelve una cadena que
        //se puede o no imprimir
        //Eventos:
        //1: Ataque de ratas
        //2: Enfermedad
        void info();
};


