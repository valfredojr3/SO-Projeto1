#ifndef PROCESS_H
#define PROCESS_H

class Process{

  public:

      Process(int id, int arrivalTime, int durationTime);

      ~Process();

      int id,
          arrivalTime,
          durationTime,
          waitTime,
          returnTime,
          responseTime,
          waitTime,
          runTime;

};

#endif
