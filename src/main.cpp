#include "Data.h"
#include "HashTable.h"
#include "Timer.h"

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::to_string;
using std::stringstream;

int randNum;

void write_csv() {
    std::ofstream myfile;
    myfile.open("relatorio.csv");
    myfile << "dados" << "\n";
    myfile.close();
}

int main() {
    std::cout << "ola" << (9+9) << std::endl; 
    
    Urna * urna = new Urna(2,2);

    int rand_num;
    int rand_num_estado;
    char *estados[27] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES",
    "GO", "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI",
    "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};
    
    for (int i=0; i<1000; i++) {
        rand_num = rand()%100;
        rand_num_estado = rand()%(7);
        Timer timer;
        urna-> insert_voto(i, rand_num, estados[rand_num_estado]);
        timer.Stop();
    }

    for (int i=0; i<1000; i++) {
        Timer timer;
        urna->search(i);
        timer.Stop();
    }
}