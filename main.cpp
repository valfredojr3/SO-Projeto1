#include <iostream>
#include <fstream>
#include <iomanip>
#include "process.hpp"

std::vector <Process> GetInput(const char* inputfile){

    std::ifstream file;
    file.open(str, std::ios::in);

    int id = 1;
    std::vector <Process> processList;

    while(file.good()){

        int processArrivalTime, processDurationtime;

        file >> processArrivalTime;
        file >> processDurationtime;

        Process newProcess(id, processStartTime, processDurationtime);
        processList.push_back(newProcess);

        ++id;

    }

    file.close();

    return processList;

}

int main(){

    std::cout << std::fixed << std::setprecision(1);

    std::vector <Process> processList = getProcessList("input.txt");

    Scheduler fcfs, sjf, rr;

    fcfs.FCFS(processList);
    sjf.SJF(processList);
    rr.RR(processList);

    return 0;
}
