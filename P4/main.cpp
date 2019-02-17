# include <iostream>
# include <stdlib.h>
# include <time.h>
# include "CPU.h"
# include "Process.h"

#define RUNS 5

const unsigned QUANTUM = 100;
extern const unsigned RUN_TIME = 60000; // milliseconds
extern const unsigned JOB_COUNT = 150;
extern const unsigned NUM_PAGES = 100;
extern const std::map<Replacement, std::string> ReplacementString;

int main() {
    srand(time(NULL));

    //Iterate over all 5 algorithms
    for(int algorithmInt = FIFO; algorithmInt != RANDOM + 1; ++algorithmInt) {
        Replacement algorithm = static_cast<Replacement>(algorithmInt);
        //Each algorithm is run 5 times to get an average
        double average = 0;
        for(int i = 0; i < RUNS; ++i) {
            CPU cpu = CPU(algorithm);
            while (!cpu.isProcessesComplete()
                   && cpu.getClockTime() <= RUN_TIME) {
                Process *p = cpu.getNextProcess();
                cpu.runProcess(QUANTUM, p);
            }
            average += cpu.getRatio();
        }
        std::cout << ReplacementString.find(algorithm)->second;
        std::cout << ": " << average << std::endl;
    }
}
