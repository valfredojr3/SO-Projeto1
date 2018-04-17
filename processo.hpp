#ifndef PROCESSO_H
#define PROCESSO_H

class Processo{

  public:

      Processo(int tempoChegada, int tempoDuracao);

      ~Processo();

      int tempoChegada,
          tempoDuracao,
          tempoProcessado;

};

#endif
