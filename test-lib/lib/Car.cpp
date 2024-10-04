#include <iostream>
#include <cstring>
#include "Car.hpp"



// static members should exist outside the class as they are not dependant of any instance 
// Define the static member outside the class (mandatory)
int Car::wheels = 0;


Car::Car(float n_peso, const char* n_cor) {
    peso = n_peso;

    cor = new char[strlen(n_cor) + 1];
    strcpy(cor, n_cor);

    matricula = nullptr; // Initialize matricula as null
    std::cout<<">> Class Car << "<<std::endl;
}

void Car::setWheels(int number) {
    Car::wheels = number;
}

void Car::setMatricula(const char* value) {
    // if matricula was already set, free the old memory
    if(this->matricula != nullptr) {
        delete[] this->matricula;
    }

    // allocate new memory and copy the string
    this->matricula = new char[strlen(value) + 1 ];
    strcpy(this->matricula, value);
}


// destructor to clean up
Car::~Car() {
    delete[] cor;
    delete[] matricula;
}

