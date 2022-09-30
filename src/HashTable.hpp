#include "HashTable.h"


HashTable::Voto::Voto(int id_usuario, int id_candidato, char regiao){
    this->id_usuario = id_usuario;
    this->id_candidato = id_candidato;
    this->regiao = regiao;
    
}

HashTable::Cand::Cand(int id,char nome){
    this->candidato_id = id;
    this->candidato_nome = nome;

}

HashTable::HashTable(){ } // ver melhor dps

void HashTable::insert_cadidato(int candidato_id, char candidato_nome){
    int hash = this->hash_cand(candidato_id);

    this->tabela_cand[hash] = new Cand(candidato_id,candidato_nome); 
    this->quant_c += 1;
    float alpha = this->quant_c / this->size_c;
    if (alpha>0.75){
        this->resize_cand();
    }

}

void HashTable::insert_voto(int id_usuario, int id_candidato, char regiao){ //esquecer da data por enquanto

    this->tabela_votos[this->quant_v] = new Voto(id_usuario, id_candidato,  regiao);

    this->quant_v += 1;
    
    if (this->quant_v == this->size_v){
        this->resize_voto();
    }
    
}


HashTable::Voto* HashTable::search(int recibo){
    // aqui to so retornando oq ele pede, não sei se tem q mostrar alguma coisa a mais
    // ou se tem q dar um print bonitinho da pessoa e as coisas do recibo
    // mas isso é coisa boba q tem q resolver dps, para achar o voto desse recibo é so isso
    return this->tabela_votos[recibo];

} 
