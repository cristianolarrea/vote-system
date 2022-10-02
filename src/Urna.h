#ifndef URNA
#define URNA

#include <ctime>

class Urna{ 
    // Estrutura usada para salvar as data que o voto foi computado
    struct Data
    {
        int ano; 
        int mes;
        int dia;
        int hora;
        int minuto;
        int segundo;
        
        Data(int);
        Data(int ano,int mes,int dia,int hora=0,int minuto=0,int segundo=0);

    };

    // Estrutura completa do voto
    struct Voto
    {
        int recibo; 
        int id_usuario;
        int id_candidato;
        char regiao[2]; 
        Data * data_voto;
    
        Voto();
    };

    // Estrutura completa do candidato 
    struct Cand
    {
        int candidato_id; 
        char candidato_nome[30]; 
        int quantidade_votos;
        Cand();
    };

    // Tamanho da tabela de votos
    int size_v; 
    // quantidade de votos
    int quant_v;

    // Tamanho da tabela de candidatos
    int size_c;
    // quantidade de cantidados ativos
    int quant_c;
    
    // Onde guardo os votos
    Voto * tabela_votos;
    
    // Onde guardo os candidatos
    Cand * tabela_cand;

  

    public: 
        Urna(int size_votos,int size_cand);

        ~Urna();

        void insert_candidato(int candidato_id, const char candidato_nome[]);

        int insert_voto(int id_usuario, int id_candidato, char regiao[2]); 
        // buscando por algum recibo
        Voto search(int recibo); 
        // relatorio com a opção de não ser passado o UF
        void relatorio_votos(char UF[2] = "NN"); 
        // Relatorio de candidato caso seja passado data de inicio e fim
        void relatorio_candidato(Data inicio,Data fim); 
        // Relatorio de candidato caso nao seja passado data de inicio e fim
        void relatorio_candidato();

    private:
        // redefine o tamanho do array de votos
        void resize_voto(); 
        // redefine o tamanho da tabela hash de candidatos
        void resize_cand(); 
        // comparação das datas
        bool a_mais_recente_que_b(Data data_a, Data data_b);
        // funcao hash
        int hash(int key);
        // realiza a  busca do indice de um key na tabela hash
        int busca_por_hash(int key);

};

#include "Urna.hpp"

#endif  // URNA


