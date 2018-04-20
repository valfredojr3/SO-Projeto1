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

/* Método do algoritmo de escalonamento FCFS (First-Come First Served) */
void Escalonador::FCFS(std::vector <Processo> listaProcesso){

    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    /* Ordena a lista de processos com base no tempo de chegada */
    std::sort(listaProcesso.begin(), listaProcesso.end(), ComparaProcessoChegada);

    /* Enquanto houverem processos para serem avaliados */
    while(listaProcesso.size() != 0){

        /* Retira o primeiro processo da lista */
        Processo aux = listaProcesso[0];
        listaProcesso.erase(listaProcesso.begin());

        /* Atualiza o tempo executado caso o tempo de chegada do próximo processo
           seja maior do que o tempo executado atualmente */
        if(aux.tempoChegada > tempoExecutado){
            tempoExecutado = aux.tempoChegada;
        }

        /* Atualiza os valores dos tempos de acordo */
        tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);
        tempoEsperaTotal += (tempoExecutado - aux.tempoChegada);
        tempoRetornoTotal += (tempoExecutado + aux.tempoDuracao - aux.tempoChegada);
        tempoExecutado += aux.tempoDuracao;

    }

    /* Calcula os resultados e os apresenta no console */
    this->tempoRespostaMedio = ((float) tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float) tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float) tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "FCFS " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
               << " " << this->tempoEsperaMedio << std::endl;

}

/* Método do algoritmo de escalonamento SJF (Shortest Job First) */
void Escalonador::SJF(std::vector <Processo> listaProcesso){

    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    /* Criada uma lista de processos para servir como a fila de processos prontos */
    std::vector <Processo> filaPronto;

    /* Enquanto houverem processos para serem avaliados */
    while(filaPronto.size() > 0 || listaProcesso.size() > 0){

	/* Caso não tenha nenhum processo pronto é necessário encontrar o
           menor tempo de chegada e adicionar ao tempo executado */
        if(filaPronto.size() == 0){

           int menorTempoChegada = INT_MAX;

           for(int j = 0; j < listaProcesso.size(); j++){

               if(listaProcesso[j].tempoChegada < menorTempoChegada)
                   menorTempoChegada = listaProcesso[j].tempoChegada;
           }

           if(menorTempoChegada > tempoExecutado)
               tempoExecutado = menorTempoChegada;
        }


       /* Percorre a lista de processos, retira todos os processos que tem
          o tempo de chegada menor ou igual ao tempo executado e os coloca
          na lista de processos prontos  */
       for(int i = 0; i < listaProcesso.size(); i++){
           if(listaProcesso[i].tempoChegada <= tempoExecutado){
               filaPronto.push_back(listaProcesso[i]);
               listaProcesso.erase(listaProcesso.begin()+i);
               i--;
           }
       }

       /* Ordena a lista de processos prontos com base no tempo de duração*/
       std::sort(filaPronto.begin(), filaPronto.end(), ComparaProcessoDuracao);

       /* Retira o primeiro processo da lista de processos prontos */
       Processo aux = filaPronto[0];
       filaPronto.erase(filaPronto.begin());

       /* Atualiza os valores dos tempos de acordo */
       tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);
       tempoEsperaTotal += (tempoExecutado - aux.tempoChegada);
       tempoRetornoTotal += (tempoExecutado + aux.tempoDuracao - aux.tempoChegada);
       tempoExecutado += aux.tempoDuracao;

    }

    /* Calcula os resultados e os apresenta no console */
    this->tempoRespostaMedio =((float)tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float)tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float)tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "SJF " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}

/* Método do algoritmo de escalonamento RR (Round Robin) com quantum = 2 */
void Escalonador::RR(std::vector <Processo> listaProcesso){

    int tempoRetornoTotal = 0;
    int tempoRespostaTotal = 0;
    int tempoEsperaTotal = 0;
    int tempoExecutado = 0;
    const int numProcessos = listaProcesso.size();

    /* Criada uma lista de processos para servir como a fila de processos prontos */
    std::vector <Processo> filaPronto;

    /* Ordena a lista de processos com base no tempo de chegada */
    std::sort(listaProcesso.begin(), listaProcesso.end(), ComparaProcessoChegada);

    /* Enquanto houverem processos para serem avaliados */
    while(filaPronto.size() > 0 || listaProcesso.size() > 0){

	/* Caso não tenha nenhum processo pronto, adiciona o menor tempo de
           chegada como tempo executado */
        if(filaPronto.size() == 0){

            tempoExecutado = listaProcesso[0].tempoChegada;

        }

	/* Adiciona à lista de processos prontos todos os processos com tempo
           de chegada menor ou igual ao tempo executado */
        for(int i = 0; i < listaProcesso.size(); i++){
            if(listaProcesso[i].tempoChegada <= tempoExecutado){
                filaPronto.push_back(listaProcesso[i]);
                listaProcesso.erase(listaProcesso.begin()+i);
                i--;
            }
        }

	/* Retira o primeiro processo da lista de processos prontos */
        Processo aux = filaPronto[0];
        filaPronto.erase(filaPronto.begin());

	/* Se o processo não tiver sido processado nem uma vez ainda,
	   aumenta o valor do tempo de resposta */
        if(aux.tempoProcessado == 0){
            tempoRespostaTotal += (tempoExecutado - aux.tempoChegada);
        }

	/* Se o processo estiver precisando de menos do que o valor de quantum
           para terminar de ser processado, aumentar adequadamente os valores
           de tempo executado e tempo processado */
        if((aux.tempoDuracao - aux.tempoProcessado) < quantum){

            tempoExecutado += (aux.tempoDuracao - aux.tempoProcessado);
            aux.tempoProcessado += (aux.tempoDuracao - aux.tempoProcessado);

	/* Senao, apenas processe o tempo de quantum desse processo */
        }else{

            aux.tempoProcessado += quantum;
            tempoExecutado += quantum;

        }

	/* Caso o processo tenha sido completamente processado, atualizar as informações
           de tempo de retorno e espera */
        if(aux.tempoProcessado == aux.tempoDuracao){

            tempoRetornoTotal += tempoExecutado - aux.tempoChegada;
            tempoEsperaTotal += tempoExecutado - aux.tempoChegada - aux.tempoDuracao;


	/* Caso o processo não tenha sido completamente processado, adicionar a lista de processos
           prontos todos os processos que possam ter chegado após a execução do tempo do quantum,
           e por fim, adicionar o processo não finalizado no fim lista de processos prontos */
        }else{

            for(int i = 0; i < listaProcesso.size(); i++){
                if(listaProcesso[i].tempoChegada <= tempoExecutado){
                    filaPronto.push_back(listaProcesso[i]);
                    listaProcesso.erase(listaProcesso.begin()+i);
                    i--;
                }
            }

            filaPronto.push_back(aux);
        }
    }

    /* Calcula os resultados e os apresenta no console */
    this->tempoRespostaMedio =((float)tempoRespostaTotal) / ((float)numProcessos);
    this->tempoRetornoMedio = ((float)tempoRetornoTotal) / ((float)numProcessos);
    this->tempoEsperaMedio = ((float)tempoEsperaTotal) / ((float)numProcessos);

    std::cout << "RR " << this->tempoRetornoMedio << " " << this->tempoRespostaMedio
            << " " << this->tempoEsperaMedio << std::endl;
}
