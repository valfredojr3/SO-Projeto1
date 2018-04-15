#include "processo.hpp"

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
