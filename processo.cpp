#include "processo.hpp"

/* Construtor do Processo que o tempo de chegada e o tempo de duração
   de execução, além disso inicia o atributo de tempo processado em 0 */
Processo::Processo(int tempoChegada, int tempoDuracao){

    this->tempoChegada = tempoChegada;
    this->tempoDuracao = tempoDuracao;
    this->tempoProcessado = 0;

}

Processo::~Processo(){;}
