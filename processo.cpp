#include "processo.hpp"

/* Construtor do Processo que recebe id, tempo de chegada e o tempo de duração
   de execução, além disso inicia os outros atributos em 0*/
Processo::Processo(int id, int tempoChegada, int tempoDuracao){

    this->id = id;
    this->tempoChegada = tempoChegada;
    this->tempoDuracao = tempoDuracao;

    this->tempoRetorno = 0;
    this->tempoResposta = 0;
    this->tempoEspera = 0;
    this->tempoProcessado = 0;

}

Processo::~Processo(){;}
