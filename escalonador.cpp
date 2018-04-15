#include "escalonador.hpp"

Escalonador::Escalonador(){

    this->tempoEsperaMedio = 0;
    this->tempoRetornoMedio = 0;
    this->tempoRespostaMedio = 0;
}

Escalonador::~Escalonador(){;}

bool ComparaProcessoChegada(Processo p1, Processo p2){
        return (p1.tempoChegada < p2.tempoChegada);
}

bool ComparaProcessoDuracao(Processo p1, Processo p2){
        return (p1.tempoDuracao < p2.tempoDuracao);
}

void Escalonador::FCFS(std::vector <Processo> listaProcesso){

    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    std::vector <Processo> listaProcessoAtivo = listaProcesso;

    std::sort(listaProcessoAtivo.begin(), listaProcessoAtivo.end(), ComparaProcessoChegada);

    while(listaProcessoAtivo.size() != 0){

        Processo aux = listaProcessoAtivo[0];
        listaProcessoAtivo.erase(listaProcessoAtivo.begin());

        if(aux.tempoChegada > tempoExecutado){
            tempoExecutado = aux.tempoChegada;
        }

        tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);
        tempoEsperaTotal += (tempoExecutado - aux.tempoChegada);
        tempoRetornoTotal += (tempoExecutado + aux.tempoDuracao - aux.tempoChegada);
        tempoExecutado += aux.tempoDuracao;

    }

    this->tempoRespostaMedio = ((float) tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float) tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float) tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "FCFS " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
               << " " << this->tempoEsperaMedio << std::endl;

}

void Escalonador::SJF(std::vector <Processo> listaProcesso){

    std::cout << "SJF " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}

void Escalonador::RR(std::vector <Processo> listaProcesso){

    std::cout << "RR " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}
