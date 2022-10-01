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

void generate_name(char* name) {
	static const int namelen = 15;
	
	static const char* letters[2] = { "bcdfghjklmnpqrstvwxyz", "aeiouy" };
	static const int letterlen[2] = { sizeof(letters[0]), sizeof(letters[1]) };
	
	for (int i=0; i<namelen; i++)
		name[i] = letters[i%2][rand()%letterlen[i%2]];
	name[0] = toupper(name[0]);
}

int main() {    
    Urna * urna = new Urna(100,50);

    char name[30];

    for (int i=0; i<50; i++) {
        generate_name(name);
        urna->insert_candidato(rand(), name);
    }

    int rand_num;
    int rand_num_estado;
    char *estados[27] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES",
    "GO", "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI",
    "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};
    
    int recibo;
    for (int i=0; i<100000000; i++) {
        rand_num_estado = rand()%(27);
       // Timer timer;
        recibo = urna-> insert_voto(rand()%(1501), rand(), estados[rand_num_estado]);
       // timer.Stop();
    }

    for (int i=0; i<1000; i++) {
        Timer timer;
        urna->search(i);
        timer.Stop();
    }
}