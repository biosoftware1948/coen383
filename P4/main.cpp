# include <iostream>
# include <stdlib.h>
# include <time.h>
# include "CPU.h"
# include "Process.h"

#define RUNS 5

const unsigned PAGE_REQUESTS = 100;
const unsigned QUANTUM = 100;
extern const unsigned RUN_TIME = 60000; // milliseconds
extern const unsigned JOB_COUNT = 150;
extern const unsigned NUM_PAGES = 100;
extern const std::map<Replacement, std::string> ReplacementString;

void runAvgOfFive();
void runWithTrace();

int main() {
    srand(time(NULL));

    runAvgOfFive();
    runWithTrace();
}

/*   Run simulator 5 times, each to complete the one minutes, and compute
 *   the hit/miss ratio of pages referenced by the running jobs for each
 *   run. Then get average of 5 runs. */
void runAvgOfFive() {
    std::cout << "========== RUNNING EACH ALGORITHM 5 TIMES TO GET AVG STATS ==========" << std::endl;
     for(int algorithmInt = FIFO; algorithmInt != RANDOM + 1; ++algorithmInt) {
         Replacement algorithm = static_cast<Replacement>(algorithmInt);
         std::string algorithmString = ReplacementString.find(algorithm)->second;
         std::cout << std::endl << "----- Running with " << algorithmString;
         std::cout << " replacement. -----" << std::endl;

         //Each algorithm is run 5 times to get an average
         double hitMissRatio = 0, processesStarted = 0;
         for(int i = 0; i < RUNS; ++i) {
             CPU cpu = CPU(algorithm);
             while (!cpu.isProcessesComplete()
                     && cpu.getClockTime() <= RUN_TIME) {
                 Process *p = cpu.getNextProcess();
                 cpu.runProcess(QUANTUM, p);
             }
             std::cout << "Run " << i << ": " << cpu.getRatio();
             std::cout << " hit/miss ratio." << std::endl;
             hitMissRatio += cpu.getRatio();
             processesStarted += cpu.getProcessesStarted();
         }
         hitMissRatio /= RUNS;
         processesStarted /= RUNS;

         std::cout << std::endl << algorithmString << " AVERAGE: ";
         std::cout << hitMissRatio << " hit miss ratio." << std::endl;
         std::cout << "Average number of successfully swapped in processes: ";
         std::cout << processesStarted << "." << std::endl << std::endl;
     }
}

/*  Run the simulator for 100 page references, and for each reference, print
 *  all the print statements listed in the project guide. */
void runWithTrace() {
    std::cout << "========== RUNNING EACH ALGORITHM FOR 100 PAGE REQUESTS WHILE PRINTING CPU/MEMORY STATES ==========" << std::endl;
     for(int algorithmInt = FIFO; algorithmInt != RANDOM + 1; ++algorithmInt) {
         Replacement algorithm = static_cast<Replacement>(algorithmInt);
         std::string algorithmString = ReplacementString.find(algorithm)->second;
         std::cout << std::endl << "----- Running with " << algorithmString;
         std::cout << " replacement. -----" << std::endl;

         unsigned i = 0;
         CPU cpu = CPU(algorithm, true);
         while (!cpu.isProcessesComplete() && i < PAGE_REQUESTS) {
             Process *p = cpu.getNextProcess();
             cpu.runProcess(QUANTUM, p);
             i++;
         }
         std::cout << std::endl;
         std::cout << "Number of swapped in processes: ";
         std::cout << cpu.getProcessesStarted() << std::endl;
         std::cout << "Hit/Miss Ratio: " << cpu.getRatio() << std::endl;
     }
}
