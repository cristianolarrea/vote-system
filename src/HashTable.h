#ifndef HASH_TABLE
#define HASH_TABLE
#include "Data.h"
#include <ctime>

class Urna{ // mudar esse nome

    struct Voto
    {
        int recibo; 
        int id_usuario;
        int id_candidato;
        char regiao; //!!! vetor de 2 letras, não lembro agora, ACHO Q É ISSO
        Data * data_voto; //perguntar sobre, acho q tem q usar uma biblioteca pega a hora certinho de quando computa 1 voto, lembro do prof flaar algo assim
    
        Voto(); // tirei a data por enquanto
    };

    struct Data
    {
        int ano; 
        int mes;
        int dia;
        int hora;
        int minuto;
        int segundo;
        
        Data(int);
    

    };

    struct Voto
    {
        int recibo; 
        int id_usuario;
        int id_candidato;
        char regiao[2]; //!!! vetor de 2 letras, não lembro agora, ACHO Q É ISSO
        Data * data_voto; //perguntar sobre, acho q tem q usar uma biblioteca pega a hora certinho de quando computa 1 voto, lembro do prof flaar algo assim
    
        Voto(); // tirei a data por enquanto
    };


    // id do candidato pode ser qualquer um
    // diferente do hashtable q usamos para os votos
    // q n precisa de hash pq o marcador do lugar é o recibo 
    // q cresce de 1 em 1, o candidato pode ter ID 1 e outro 213
    // ai precisa de hash para n fazer uma tabela mt grande
    struct Cand
    {
        int candidato_id; 
        char candidato_nome[30]; // ver como faz pra salvar string

        Cand();
    };

    int size_v; 
    int quant_v;

    int size_c;
    int quant_c;
    
    Voto * tabela_votos;// ver melhor isso de comecar fixo, qria colocar o size aq
    
    Cand * tabela_cand;// ver melhor isso de comecar fixo


    public: 
        Urna(int size_votos,int size_cand);

        ~Urna();

        void insert_candidato(int candidato_id, const char candidato_nome[]);

        // ser capaz de votar
        void insert_voto(int id_usuario, int id_candidato, char regiao[2]); //esquecer da data por enquanto
        
        // ser capaz de achar o voto com o recibo
        Voto search(int recibo); // n tenho certeza se esse é o retorno
        
        // um adm devera ser capaz de soliciar um relatorio com todos os votos ate o momento
        void relatorio_votos(); // ainda não sei oq vai retornar direito, talvez uma lista de ponteiros de voto
        
        // um adm pode soliciar relatorio com top10 candidatos
        void relatorio_candidato(); // ainda não sei o retorno

    private:
        //unsigned hash(unsigned key);
        
        void resize_voto(); // feito 

        int hash_cand(int ); // feito 
        void resize_cand(); // feito 
        
        bool a_mais_recente_que_b(Data data_a, Data data_b);

};

#include "HashTable.hpp"

#endif  // HASH_TABLE

// ver coisa da data (fala q pode usar biblioteca para obter data corrente)
// ver melhor o resize
// Instrumente as operações de forma que o tempo de execução seja medido a cada execução ?????
// produza um grafico ?????? se pahq  é pro relatorio, da pra anotar os resultados de medição e fazer em python
// tomar cuidado com qualidade de codigo