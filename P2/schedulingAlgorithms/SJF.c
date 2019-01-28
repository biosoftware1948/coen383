# include "../CPU.h"
# include "../Job.h"
# include "SJF.h"

void RunSJF(CPU *cpu, Job *jobs, unsigned jobsCount) {
    sort_by_arrival_time(jobs, jobsCount);
    printf("\n\nTESTING\n\n");
    printAllJobs(jobs, jobsCount);
}
