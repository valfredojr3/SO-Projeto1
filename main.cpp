/*  Aluno: Valfredo Santos Júnior
    Matricula: 115040304  */

#include <fstream>
#include <iomanip>

#include "processo.hpp"
#include "escalonador.hpp"

/*  Função CriaLista recebe como parâmetro um endereço para o arquivo de entrada
    aberto no main, cria uma lista de objetos do tipo Processo com base na
    entrada, e retorna essa lista.  */
std::vector <Processo> CriaLista(const char* inputfile){

    std::ifstream file;
    file.open(inputfile, std::ios::in);

    std::vector <Processo> listaProcesso;

    while(file.good()){

        int tempoChegada, tempoDuracao;

        file >> tempoChegada;
        file >> tempoDuracao;

        Processo auxProcesso(tempoChegada, tempoDuracao);
        listaProcesso.push_back(auxProcesso);

    }

    file.close();

    return listaProcesso;

}

/*  O main define a precisão da casa decimal para um, faz a criação da
    lista de processos com base na entrada, cria três objetos da classe Escalonador
    e então chama uma função para cada algoritmo de escalonamento, passando a
    lista de processos como parâmetro */
int main(){

    std::cout << std::fixed << std::setprecision(1);

    std::vector <Processo> listaProcesso = CriaLista("input.txt");

    Escalonador fcfs, sjf, rr;

    fcfs.FCFS(listaProcesso);
    sjf.SJF(listaProcesso);
    rr.RR(listaProcesso);

    return 0;
}
