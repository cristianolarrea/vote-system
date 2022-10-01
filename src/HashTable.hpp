#include "HashTable.h"
#include <iostream>
#include <ctime>
#include <fstream>

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

Urna::Data::Data(int ano,int mes,int dia,int hora,int minuto,int segundo){
        this->ano=ano; 
        this->mes=mes;
        this->dia=dia;
        this->hora=hora;
        this->minuto=minuto;
        this->segundo=segundo;
}

Urna::Voto::Voto(){}

Urna::Cand::Cand(){}

Urna::Urna(int size_votos,int size_cand){ 
    this->size_v = size_votos;
    this->size_c = size_cand;
    this->quant_c = 0;
    this->quant_v = 0;

    this->tabela_votos = new Voto[this->size_v];

    this->tabela_cand = new Cand[this->size_c];
    for (int i =0;i<this->size_c;i++){
        this->tabela_cand[i] = * new Cand();

        this->tabela_cand[i].candidato_id=-1;
        this->tabela_cand[i].quantidade_votos=0;

    }
}
 
void Urna::insert_candidato(int candidato_id,const char candidato_nome[]){
    int hash_ = this->hash(candidato_id);

    while(this->tabela_cand[hash_].candidato_id != -1){
        hash_ = hash_+1;
        if (hash_>=this->size_c)
            hash_=0;
    }

    this->tabela_cand[hash_].candidato_id=candidato_id;
    for (int i=0; i<sizeof(candidato_nome); i++) {
            this->tabela_cand[hash_].candidato_nome[i]=candidato_nome[i];
    }
    std::cout << "Candidato id: "<<this->tabela_cand[hash_].candidato_id <<std::endl;
    std::cout << "Indice que esta: "<< hash_ <<std::endl;

    this->quant_c += 1;
    float alpha = (this->quant_c/this->size_c);
    if (alpha>0.75){
        this->resize_cand();
    }

}

void Urna::insert_voto(int id_usuario, int id_candidato, char regiao[]){ 

    this->tabela_votos[this->quant_v] = * new Voto(); 
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

void Urna::resize_voto(){
    int newSize = this->size_v * 2;
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
    for (int i =0 ; i<newSize ; i++){
        newTable[i] = * new Cand();

        newTable[i].candidato_id=-1;
        newTable[i].quantidade_votos=0;
    }
    

    for (int i = 0; i < this->size_c; i++){
        int hash_ = this->hash(this->tabela_cand[i].candidato_id);

        while(newTable[hash_].candidato_id != -1){
            hash_ = hash_+1;
            if (hash_>=newSize) 
                hash_=0;
        }
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

void Urna::swap_cand( int i, int j){
    Cand temp = this->tabela_cand[i]; 
    this->tabela_cand[i] = this->tabela_cand[j];
    this->tabela_cand[j] = temp; 
}

void Urna::heapify_cand( int n, int i){
    int inx = i;
    int leftInx = 2 * i + 1;
    int rightInx = 2 * i + 2;
    if ((leftInx < n) && (this->tabela_cand[leftInx].candidato_id > this->tabela_cand[inx].candidato_id)) {
        inx = leftInx;
    }
if ((rightInx < n) && (this->tabela_cand[rightInx].candidato_id > this->tabela_cand[inx].candidato_id)) {
        inx = rightInx;
    }
if (inx != i) {
        this->swap_cand( i, inx);
        this->heapify_cand( n, inx);
    }
}

void Urna::heapSort_cand(int n) {
    for (int i=(n/2-1); i >= 0; i--) {
        this->heapify_cand(n, i);
    }
    for (int i=n-1; i > 0; i--) {
        this->swap_cand( 0, i);
        this->heapify_cand( i, 0);
    }
}

int Urna::Busca_binaria_cand(int leftInx, int rightInx, int x) {
    int midInx = (leftInx + rightInx) / 2;
    int midValue = this->tabela_cand[midInx].candidato_id;
    if (midValue == x) {
        return midInx;
    }
    if (leftInx >= rightInx) {
        return -1;
    }
    if (x > midValue) {
        return this->Busca_binaria_cand(midInx + 1, rightInx, x);
    } else {
        return this->Busca_binaria_cand( leftInx, midInx - 1, x);
    }
}

int Urna::busca_por_hash(int key){
    int hash_ = this->hash(key);

    while(this->tabela_cand[hash_].candidato_id != key){
    hash_ = hash_+1;
    if (hash_>=this->size_c)
        hash_=0;
    }
    return hash_;
}


void Urna::relatorio_votos(char UF[2]){ 
    std::ofstream myfile;
    myfile.open ("Relatorio_Votos.csv");
    myfile <<""<<";"<< "ID do Usuario" << ";"<<"Candidato"<<";"<<"Data"<< ";" <<"Estado"<< "\n";

    int recibo;
    int id_usuario;
    char candidato[30];
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
    char sigla_1;
    char sigla_2;
    int index_cand;
    int hash_;

    for(int i = 0; i<this->quant_v; i++){
        sigla_1 = this->tabela_votos[i].regiao[0];
        sigla_2 = this->tabela_votos[i].regiao[1];

        if ((sigla_1 == UF[0] && sigla_2 == UF[1])||('N' == UF[0] && 'N' == UF[1]) ){
            hash_ = this->busca_por_hash(this->tabela_votos[i].id_candidato);

            for (int p=0; p<sizeof(this->tabela_cand[hash_].candidato_nome); p++) {
                candidato[p]=this->tabela_cand[hash_].candidato_nome[p];
            }

            recibo = this->tabela_votos[i].recibo;
            id_usuario = this->tabela_votos[i].id_usuario;
            ano = this->tabela_votos[i].data_voto->ano;
            mes = this->tabela_votos[i].data_voto->mes;
            dia = this->tabela_votos[i].data_voto->dia;
            hora = this->tabela_votos[i].data_voto->hora;
            minuto = this->tabela_votos[i].data_voto->minuto;
            segundo = this->tabela_votos[i].data_voto->segundo;

            myfile <<recibo<<";"<< id_usuario << ";"<<candidato<<";"<< dia <<"/" << mes <<"/" << ano << " - " << hora<<":"<<minuto<<":"<<segundo << ";" <<sigla_1<< sigla_2<< "\n";
    }}

    myfile.close();
}

int Urna::hash(int key){
    return (key%this->size_c);
}

void Urna::relatorio_candidato(Data inicio, Data fim){
    int hash_;
    int max;
    int index_max;
    Data* data_atual;
    std::ofstream myfile;
    myfile.open ("Top_10_Candidatos.csv");
    myfile <<"Posicao"<<";"<< "Nome Candidato" << ";"<<"Quantidade de Votos" << "\n";
    
    for (int i=0;i<this->quant_v;i++){
        data_atual = this->tabela_votos->data_voto;
        if(a_mais_recente_que_b(*data_atual,inicio) &&  a_mais_recente_que_b(fim,*data_atual)) {

        hash_ = this->busca_por_hash(this->tabela_votos[i].id_candidato);
        this->tabela_cand[hash_].quantidade_votos++;
    }
    }
    for (int o = 0; o < 10 ; o++){
        max=-1;
        index_max=0;

        for(int i = 0; i < this->size_c; i++){
            if(this->tabela_cand[i].quantidade_votos>max){
                max = this->tabela_cand[i].quantidade_votos;
                index_max=i;
            }
        }
        myfile << (o+1) << ";" << this->tabela_cand[index_max].candidato_nome <<";"<< max << "\n";
        this->tabela_cand[index_max].quantidade_votos=0;
    }

    for(int i = 0; i < this->size_c; i++){
        this->tabela_cand[i].quantidade_votos = 0;
    }
}

void Urna::relatorio_candidato(){
    int hash_;
    int max;
    int index_max;
    std::ofstream myfile;
    myfile.open ("Top_10_Candidatos.csv");
    myfile <<"Posicao"<<";"<< "Nome Candidato" << ";"<<"Quantidade de Votos" << "\n";
    
    for (int i=0;i<this->quant_v;i++){      
        hash_ = this->busca_por_hash(this->tabela_votos[i].id_candidato);
        this->tabela_cand[hash_].quantidade_votos++;
    }
    for (int o = 0; o < 10 ; o++){
        max=-1;
        index_max=0;

        for(int i = 0; i < this->size_c; i++){
            if(this->tabela_cand[i].quantidade_votos>max){
                max = this->tabela_cand[i].quantidade_votos;
                index_max=i;
            }
        }
        myfile << (o+1) << ";" << this->tabela_cand[index_max].candidato_nome <<";"<< max << "\n";
        this->tabela_cand[index_max].quantidade_votos=0;
    }

    for(int i = 0; i < this->size_c; i++){
        this->tabela_cand[i].quantidade_votos = 0;
    }
}