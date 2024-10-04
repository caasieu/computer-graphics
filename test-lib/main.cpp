#include <iostream>
#include "lib/Car.hpp"
using namespace std;

int main(int argc, char* argv[]) {

    Car::wheels = 4;
    std::cout<<"--- Os carros têm "<<Car::wheels<<" rodas ---"<<std::endl;
    std::cout<<""<<std::endl;

    Car range;
    range.setMatricula("A3VV");
    std::cout<<"range: \n";
    std::cout<<"- matricula "<<range.matricula<<std::endl;
    std::cout<<"- cor "<<range.cor<<std::endl;
    std::cout<<"- peso "<<range.peso<<std::endl;

    std::cout<<""<<std::endl;

    Car lambo(256.50, "branca");
    lambo.setMatricula("A3VV");
    std::cout<<"lambo: \n";
    std::cout<<"- matricula "<<lambo.matricula<<std::endl;
    std::cout<<"- cor "<<lambo.cor<<std::endl;
    std::cout<<"- peso "<<lambo.peso<<std::endl;

}