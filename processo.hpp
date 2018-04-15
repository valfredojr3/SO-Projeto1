#ifndef PROCESSO_H
#define PROCESSO_H

class Processo{

  public:

      Processo(int id, int tempoChegada, int tempoDuracao);

      ~Processo();

      int id,
          tempoChegada,
          tempoDuracao,
          tempoEspera,
          tempoRetorno,
          tempoResposta,
          tempoProcessado;

};

#endif
