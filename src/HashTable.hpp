#include "HashTable.h"
#include <iostream>
#include <ctime>

Urna::Data::Data(int time){
    this->ano = 1970 + (time / 31536000);
    time = time % 31536000;

    this->mes = 1 + (time / 2592000);
    time = time % 2592000;

    this->dia = 1 + (time / 86400);
    time = time % 86400;

    this->hora = (time / 3600);
    time = time % 3600;

    this->minuto = (time / 60);
    time = time % 60;

    this->segundo = time;
}

Urna::Voto::Voto(){}

Urna::Cand::Cand(){}

Urna::Urna(int size_votos,int size_cand){ 
    this->size_v = size_votos;
    this->size_c = size_cand;

    this->tabela_votos = new Voto[this->size_v];

    this->tabela_cand = new Cand[this->size_c];
} 
 // ver melhor dps

void Urna::insert_candidato(int candidato_id,const char candidato_nome[]){
    int hash = this->hash_cand(candidato_id);

    this->tabela_cand[hash] = * new Cand(); //  aq vai ter q fazer o negocio de 
    this->tabela_cand[hash].candidato_id=candidato_id;
    for (int i=0; i<sizeof(candidato_nome); i++) {
            this->tabela_cand[hash].candidato_nome[i]=candidato_nome[i];
    }
    // colocar no da frente caso o lugar esteja ocupado, mas se pah q a gente desiste disso de colocar o candidato assim
    // e so pega uma lista quando inicializa a estrutura e armazena ela
    // Pensando melhor se pahq  vai precisar sim, para conseguir usar legal os negocios dos cand
    
    this->quant_c += 1;
    std::cout<< "Colocamos id: " << this->tabela_cand[hash].candidato_id <<std::endl;
    std::cout<< "Colocamos nome: " << this->tabela_cand[hash].candidato_nome <<std::endl;

    float alpha = this->quant_c / this->size_c;
    if (alpha>0.75){
        this->resize_cand();
    }

}

void Urna::insert_voto(int id_usuario, int id_candidato, char regiao[]){ //esquecer da data por enquanto

    this->tabela_votos[this->quant_v] = * new Voto(); // NAO TENHO IDEIA COMO ESTOU USANDO ESSAS PORRAS DE PONTEIROS
    this->tabela_votos[this->quant_v].id_candidato = id_candidato;
    this->tabela_votos[this->quant_v].id_usuario = id_usuario;
    for (int i=0; i<sizeof(regiao); i++) {
        this->tabela_votos[this->quant_v].regiao[i] = regiao[i];
    }
    this->tabela_votos[this->quant_v].recibo = this->quant_v;
    
    int timeagr = time(0);
    Data * time_ = new Data(timeagr);

    this->tabela_votos[this->quant_v].data_voto = time_;


    this->quant_v += 1;
    
    if (this->quant_v == this->size_v){
        this->resize_voto();
    }
}

Urna::Voto Urna::search(int recibo){
    // aqui to so retornando oq ele pede, não sei se tem q mostrar alguma coisa a mais
    // ou se tem q dar um print bonitinho da pessoa e as coisas do recibo
    // mas isso é coisa boba q tem q resolver dps, para achar o voto desse recibo é so isso
   
    std::cout<< "Recibo : " << this->tabela_votos[recibo].recibo <<std::endl;
    std::cout<< "Usuario : " << this->tabela_votos[recibo].id_usuario <<std::endl;
    std::cout<< "Região : " << this->tabela_votos[recibo].regiao <<std::endl;
    int ano = this->tabela_votos[recibo].data_voto->ano;
    int mes = this->tabela_votos[recibo].data_voto->mes;
    int dia = this->tabela_votos[recibo].data_voto->dia;
    int hora = this->tabela_votos[recibo].data_voto->hora;
    int minuto = this->tabela_votos[recibo].data_voto->minuto;
    int segundo = this->tabela_votos[recibo].data_voto->segundo;

    std::cout<< "Data : " << dia <<"/" << mes <<"/" << ano << " - " << hora<<":"<<minuto<<":"<<segundo<<std::endl;

    return this->tabela_votos[recibo];
    // se pah q é para fazer um print com esse recibo 
} 


int Urna::hash_cand(int candidato_id){
    return (candidato_id % this->size_c);
}

void Urna::resize_voto(){

    int newSize = this->size_v * 5;
    Voto * newTable = new Voto[ newSize];

    for (int i = 0; i < this->size_v;i++){
        newTable[i] = this->tabela_votos[i];
    }
    this->size_v = newSize;
    delete [] this->tabela_votos;

    this->tabela_votos = newTable;
}


void Urna::resize_cand(){

    int newSize = this->size_c * 5;
    Cand * newTable = new Cand[ newSize ];

    for (int i = 0; i < this->size_c; i++){
        newTable[i] = this->tabela_cand[i];
    }

    this->size_c = newSize;
    delete [] this->tabela_cand;

    this->tabela_cand = newTable;
}

bool Urna::a_mais_recente_que_b(Data data_a, Data data_b){
    if(data_a.ano > data_b.ano)
    return true;

    if(data_a.mes > data_b.mes)
    return true;

    if(data_a.dia > data_b.dia)
    return true;

    if(data_a.hora > data_b.hora)
    return true;

    if(data_a.minuto > data_b.minuto)
    return true;

    if(data_a.segundo > data_b.segundo)
    return true;

    return false;
}

