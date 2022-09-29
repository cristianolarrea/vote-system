#ifndef DATA
#define DATA

class Data {

    unsigned dia;
    unsigned mes;
    unsigned ano;

    public:
        Data(unsigned dia, unsigned mes, unsigned ano);

        Data compare(Data data1, Data data2); //Realizar overload dessa função

};

#include "Data.hpp"

#endif // DATA