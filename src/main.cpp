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
using std::vector;
using std::list;
using std::to_string;
using std::stringstream;


int main() {
    std::cout << "ola" << (9+9) << std::endl; 
    
    Urna * urna = new Urna(2,2);

    // urna->insert_voto(1,2,"RS");
    // urna->insert_voto(2,3,"RJ");
    // urna->insert_voto(3,1,"SP");
    // urna->insert_voto(6,2,"RJ");
    // urna->insert_voto(1,2,"PA");
    // urna->insert_voto(2,3,"PA");
    // urna->insert_voto(3,1,"PI");
    // urna->insert_voto(6,2,"RS");
    // urna->insert_voto(1,2,"AM");
    // urna->insert_voto(2,3,"PR");
    // urna->insert_voto(3,1,"AC");
    // urna->insert_voto(6,2,"DF");


    // urna->search(1);
    // urna->search(2);
    // urna->search(3);
    // urna->search(4);
    // urna->search(5);
    // urna->search(6);
    // urna->search(7);

    // urna->size();

    // urna->insert_candidato(1,"Fabio");
    // urna->insert_candidato(2,"Heitor");
    // urna->insert_candidato(3,"Julio");



    int * n = new int [3];

    n[0] = 1;
    n[1] = 2;
    n[2] = 3;
    n[3] = 3;
    n[4] = 3;
    n[5] = 4;

    int * p = new int[10];
    for (int i=0; i<3;i++){
        p[i]=n[i];
    }
    delete [] n;
    p[5] = 120;
 
    n=p;
    std::cout << "ola" << n[5] << std::endl;



    std::cout << "ola" << (9+9) << std::endl; 


}