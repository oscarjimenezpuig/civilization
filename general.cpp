#include "general.hpp"


double uniform(double min,double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

double normal(double m,double dt) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(m,dt);
    return dist(gen);
}


//prueba

using namespace std;

int main() {
    cout<<uniform(3,7)<<endl;
}
