#include "HashTable.h"

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

using std::stringstream;


int main() {
    std::cout << "ola" << (9+9) << std::endl; 
    
    Urna * urna = new Urna(2,2);

    urna->insert_candidato(1,"Fabio1");
    urna->insert_candidato(2,"Heitor2");
    urna->insert_candidato(3,"Julio3");
    urna->insert_candidato(4,"Romario4");
    urna->insert_candidato(10,"Julio5");
    urna->insert_candidato(50,"Romario6");
    urna->insert_candidato(90,"Fabio7");
    urna->insert_candidato(5,"Heitor");
    urna->insert_candidato(100,"Julio");
    urna->insert_candidato(110,"Romar");
    urna->insert_candidato(120,"Julio");
    urna->insert_candidato(130,"1234567891011");


    urna->insert_voto(2,1,"RS");
    urna->insert_voto(10,2,"RJ");
    urna->insert_voto(50,3,"RJ");
    urna->insert_voto(1,4,"RJ");
    urna->insert_voto(2,10,"PA");
    urna->insert_voto(3,50,"PA");
    urna->insert_voto(1,90,"PI");
    urna->insert_voto(2,5,"RS");
    urna->insert_voto(2,100,"AM");
    urna->insert_voto(3,110,"PR");
    urna->insert_voto(1,120,"AC");
    urna->insert_voto(50,130,"DF");
    urna->insert_voto(3,110,"PR");
    urna->insert_voto(1,120,"AC");
    urna->insert_voto(50,130,"DF");
    urna->insert_voto(3,110,"PR");
    urna->insert_voto(50,5,"DF");
    urna->insert_voto(50,5,"DF");
    urna->insert_voto(50,5,"DF");
    urna->insert_voto(50,5,"DF");
    urna->insert_voto(50,5,"DF");


    urna->search(1);
    urna->search(2);
    urna->search(3);
    urna->search(4);
    urna->search(5);
    urna->search(6);
    urna->search(7);

    //urna->size();



    // int * n = new int [3];

    // n[0] = 1;
    // n[1] = 2;
    // n[2] = 3;
    // n[3] = 3;
    // n[4] = 3;
    // n[5] = 4;

    // int * p = new int[10];
    // for (int i=0; i<3;i++){
    //     p[i]=n[i];
    // }
    // delete [] n;
    // p[5] = 120;
 
    // n=p;
    // std::cout << "ola" << n[5] << std::endl;

    urna->relatorio_votos("RJ");
    urna->relatorio_candidato();


}