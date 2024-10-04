
#ifndef CAR_H
#define CAR_H



class Car {
    public:
        Car(float n_peso = 0.0, const char* n_cor = ""); // constructor
        ~Car(); // destructor
        
        // static meaning every instance of this class will have a unique number of wheels
        static int wheels; 

        float peso;
        char* matricula;
        char* cor;

        static void setWheels(int number);
        void setMatricula(const char* value);

    private:
        bool playing;
};

#endif