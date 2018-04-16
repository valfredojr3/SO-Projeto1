#include "escalonador.hpp"


/* Construtor do Escalonador que inicia os atributos em 0 */
Escalonador::Escalonador(){

    this->tempoEsperaMedio = 0;
    this->tempoRetornoMedio = 0;
    this->tempoRespostaMedio = 0;
}

/* Destrutor */
Escalonador::~Escalonador(){;}

/* Métodos de comparação, recebem dois processos e informam se o primeiro é
   menor que o segundo em relação de tempo de chegada ou tempo de duração,
   utilizadas para a chamada do std::sort */
bool ComparaProcessoChegada(Processo p1, Processo p2){
        return (p1.tempoChegada < p2.tempoChegada);
}

bool ComparaProcessoDuracao(Processo p1, Processo p2){
        return (p1.tempoDuracao < p2.tempoDuracao);
}

/* Método do algoritmo de escalonamento FCFS (First-Come First Served), recebe
   uma lista de objetos do tipo Processo, trabalha em cima dos dados, e ao fim
   gera os valores de tempo de resposta médio, tempo de retorno médio e tempo de
   espera médio, salva esses valores nos atributos da classe e imprime esses
   resultados com cout */
void Escalonador::FCFS(std::vector <Processo> listaProcesso){

    //Variáveis utilizadas para calcular o tempo total e ao fim gerar a média
    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    /* Uma segunda lista de processos "ativos" recebe a cópia da primeira, então a 
       segunda lista é ordenada levando em consideração o tempo de chegada dos processos */
    std::vector <Processo> listaProcessoAtivo = listaProcesso;
    std::sort(listaProcessoAtivo.begin(), listaProcessoAtivo.end(), ComparaProcessoChegada);

    /* Um loop que percorre a lista de processos "ativos" e vai somando os tempos de
       resposta, retorno e espera totais */
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

    /* Apresenta no console os resultados */
    this->tempoRespostaMedio = ((float) tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float) tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float) tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "FCFS " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
               << " " << this->tempoEsperaMedio << std::endl;

}

/* Método do algoritmo de escalonamento SJF (Shortest Job First), recebe
   uma lista de objetos do tipo Processo, trabalha em cima dos dados, e ao fim
   gera os valores de tempo de resposta médio, tempo de retorno médio e tempo de
   espera médio, salva esses valores nos atributos da classe e imprime esses
   resultados com cout */
void Escalonador::SJF(std::vector <Processo> listaProcesso){

    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    std::vector <Processo> listaProcessoAtivo;

    /* Percorre a lista de processos e remove todos os processos com tempo
       de chegada igual a 0 e coloca na lista de processos ativos */
    for(int i = 0; i < listaProcesso.size(); i++){
        if(listaProcesso[i].tempoChegada == 0){
            listaProcessoAtivo.push_back(listaProcesso[i]);
            listaProcesso.erase(listaProcesso.begin()+i);
            i--;
        }
    }

    while(listaProcessoAtivo.size() > 0 || listaProcesso.size() > 0){

        if(listaProcessoAtivo.size() == 0 && listaProcesso.size() > 0){

           int menorTempoChegada = INT_MAX;

           for(int j = 0; j < listaProcesso.size(); j++){

               if(listaProcesso[j].tempoChegada < menorTempoChegada)
                   menorTempoChegada = listaProcesso[j].tempoChegada;
           }

           if(menorTempoChegada > tempoExecutado)
               tempoExecutado = menorTempoChegada;
        }


       for(int i = 0; i < listaProcesso.size(); i++){
           if(listaProcesso[i].tempoChegada <= tempoExecutado){
               listaProcessoAtivo.push_back(listaProcesso[i]);
               listaProcesso.erase(listaProcesso.begin()+i);
               i--;
           }
       }

       std::sort(listaProcessoAtivo.begin(), listaProcessoAtivo.end(), ComparaProcessoDuracao);

       Processo aux = listaProcessoAtivo[0];
       listaProcessoAtivo.erase(listaProcessoAtivo.begin());

       tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);

       tempoEsperaTotal += (tempoExecutado - aux.tempoChegada);

       tempoRetornoTotal += (tempoExecutado + aux.tempoDuracao - aux.tempoChegada);

       tempoExecutado += aux.tempoDuracao;

    }

    /* Apresenta no console os resultados */
    this->tempoRespostaMedio =((float)tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float)tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float)tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "SJF " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}

/* Método do algoritmo de escalonamento RR (Round Robin) com quantum = 2, recebe
   uma lista de objetos do tipo Processo, trabalha em cima dos dados, e ao fim
   gera os valores de tempo de resposta médio, tempo de retorno médio e tempo de
   espera médio, salva esses valores nos atributos da classe e imprime esses
   resultados com cout */
void Escalonador::RR(std::vector <Processo> listaProcesso){
    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    std::vector <Processo> listaProcessoAtivo;

    std::sort(listaProcesso.begin(), listaProcesso.end(), ComparaProcessoChegada);

    while(listaProcessoAtivo.size() > 0 || listaProcesso.size() > 0){

        if(listaProcessoAtivo.size() == 0 && listaProcesso.size() > 0){

            tempoExecutado = listaProcesso[0].tempoChegada;

        }

        for(int i = 0; i < listaProcesso.size(); i++){
            if(listaProcesso[i].tempoChegada <= tempoExecutado){
                listaProcessoAtivo.push_back(listaProcesso[i]);
                listaProcesso.erase(listaProcesso.begin()+i);
                i--;
            }
        }

        Processo aux = listaProcessoAtivo[0];
        listaProcessoAtivo.erase(listaProcessoAtivo.begin());

        if(aux.tempoProcessado == 0){
            tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);
        }

        if((aux.tempoDuracao - aux.tempoProcessado) < 2){

            tempoExecutado += (aux.tempoDuracao - aux.tempoProcessado);
            aux.tempoProcessado += (aux.tempoDuracao - aux.tempoProcessado);

        }else{

            aux.tempoProcessado += 2;
            tempoExecutado += 2;

        }

        if(aux.tempoProcessado == aux.tempoDuracao){

            tempoRetornoTotal += tempoExecutado - aux.tempoChegada;
            tempoEsperaTotal += tempoExecutado - aux.tempoChegada - aux.tempoDuracao;


        }else{

            for(int i = 0; i < listaProcesso.size(); i++){
                if(listaProcesso[i].tempoChegada <= tempoExecutado){
                    listaProcessoAtivo.push_back(listaProcesso[i]);
                    listaProcesso.erase(listaProcesso.begin()+i);
                    i--;
                }
            }

            listaProcessoAtivo.push_back(aux);
        }
    }

    /* Apresenta no console os resultados */
    this->tempoRespostaMedio =((float)tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float)tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float)tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "RR " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}
