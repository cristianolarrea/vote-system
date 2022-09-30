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

    urna->insert_voto(1,2,'0');
    urna->insert_voto(2,3,'1');
    urna->insert_voto(3,1,'2');
    urna->insert_voto(6,2,'3');
    urna->insert_voto(1,2,'4');
    urna->insert_voto(2,3,'5');
    urna->insert_voto(3,1,'6');
    urna->insert_voto(6,2,'7');
    urna->insert_voto(1,2,'4');
    urna->insert_voto(2,3,'5');
    urna->insert_voto(3,1,'6');
    urna->insert_voto(6,2,'7');

    urna->search(1);
    urna->search(2);
    urna->search(3);
    urna->search(4);
    urna->search(5);
    urna->search(6);
    urna->search(7);

    urna->insert_cadidato(1,'F');
    urna->insert_cadidato(2,'H');
    urna->insert_cadidato(3,'J');


}