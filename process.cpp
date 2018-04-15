#include "process.hpp"

process::process(int id, int arrivalTime, int durationTime){

    this->id = id;
    this->arrivalTime = arrivalTime;
    this->durationTime = durationTime;

    this->returnTime = 0;
    this->responseTime = 0;
    this->waitTime = 0;
    this->runTime = 0;

}
