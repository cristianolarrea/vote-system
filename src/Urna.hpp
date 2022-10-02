#include "Urna.h"
#include <iostream>
#include <ctime>
#include <fstream>

// Inicializando usando ctime, que pega em segundos
// desde 1970.
// Temos que duvidir o time assim para conseguir
// fazer a comparação posteriomente sem utilizar 
// bibliotecas que facilitam isso 
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

// Inicialização da data passada com parametros manualmente
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
// Inicializa a urna com os tamanhos iniciais dos 
// arrays de votos e de candidatos
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
 
// Adiciona os candidatos na hash table
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

    this->quant_c += 1;
    float alpha = (this->quant_c/this->size_c);
    if (alpha>0.75){
        this->resize_cand();
    }

}

// Registra um novo voto
int Urna::insert_voto(int id_usuario, int id_candidato, char regiao[]){ 

    this->tabela_votos[this->quant_v] = * new Voto(); 
    this->tabela_votos[this->quant_v].id_candidato = id_candidato;
    this->tabela_votos[this->quant_v].id_usuario = id_usuario;
    for (int i=0; i<sizeof(regiao); i++) {
        this->tabela_votos[this->quant_v].regiao[i] = regiao[i];
    }
    int recibo = this->quant_v;
    this->tabela_votos[this->quant_v].recibo = recibo;
    
    int timeagr = time(0);
    Data * time_ = new Data(timeagr);

    this->tabela_votos[this->quant_v].data_voto = time_;

    this->quant_v += 1;
    
    if (this->quant_v == this->size_v){
        this->resize_voto();
    }
    return recibo;
}

// Busca um voto por registro e retorna o voto
Urna::Voto Urna::search(int recibo){
  
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
} 

// Aumenta o tamanho do array com os votos
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

// Aumento o tamanho da tabela hash 
void Urna::resize_cand(){
    int newSize = this->size_c * 2;
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

// Função que faz a comparação das datas
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

// Encontra o indice que uma chave tem na 
// tabela hash de candidatos
int Urna::busca_por_hash(int key){
    int hash_ = this->hash(key);

    while(this->tabela_cand[hash_].candidato_id != key){
    hash_ = hash_+1;
    if (hash_>=this->size_c)
        hash_=0;
    }
    return hash_;
}

// Cria um csv com o relatorio de todos os votos
// podem ser filtrado por regiao, sendo passado por
// parametro.
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

// Função hash
int Urna::hash(int key){
    return (key%this->size_c);
}

// Cria um csv com o top 10 candidatos mais votados 
// em um periodo de datas especificados 
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

// Cria um csv com o top 10 candidatos mais votados 
// considerando todos os votos 
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