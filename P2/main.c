#include "Job.h"
#include "Queue.h"
#include "CPU.h"

int main() {
    int NUM_JOBS = 100;

    Job* jobs = createJobs(NUM_JOBS);
    printAllJobs(jobs, NUM_JOBS);

    CPU* cpu = createCPU();
    
    return 0;
}