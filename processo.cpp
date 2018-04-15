#include "processo.hpp"

processo::processo(int id, int tempoChegada, int tempoDuracao){

    this->id = id;
    this->tempoChegada = tempoChegada;
    this->tempoDuracao = tempoDuracao;

    this->tempoRetorno = 0;
    this->tempoResposta = 0;
    this->tempoEspera = 0;
    this->tempoExecutado = 0;

}
