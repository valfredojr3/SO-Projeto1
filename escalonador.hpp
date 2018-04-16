#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "processo.hpp"
#include <limits.h>

#define quantum 2

class Escalonador{

    public:

        Escalonador();

        ~Escalonador();

        void FCFS(std::vector <Processo> listaProcesso);
        void SJF(std::vector <Processo> listaProcesso);
        void RR(std::vector <Processo> listaProcesso);

        float tempoEsperaMedio;
        float tempoRetornoMedio;
        float tempoRespostaMedio;
};

#endif
