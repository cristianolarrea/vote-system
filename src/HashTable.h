#ifndef HASH_TABLE
#define HASH_TABLE
#include "Data.h"

class HashTable {
    
    struct Voto
    {
        unsigned key; //Também é o id_usuario
        unsigned recibo; //Recibo será a key
        unsigned key_candidato;
        Data data_voto;
        Voto* next;
        Voto* previous;
    };
    
    public: 
        HashTable(int size);

        ~HashTable();

        void insert_or_update(Voto voto);

        Voto* search(unsigned key);

        bool remove(unsigned key);

    private:
        unsigned hash(unsigned key);

};

#include "HashTable.hpp"

#endif  // HASH_TABLE