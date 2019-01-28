# include <assert.h>
# include "../CPU.h"
# include "../Job.h"
# include "SJF.h"

void RunSJF(CPU *cpu, Job *jobs, unsigned jobsCount) {
    int completed = 0;

    sort_by_arrival_time(jobs, jobsCount);

    while (cpu->global_time < 100 && completed < jobsCount) {
        Job *next = NULL;

        // Run CPU idle until next job arrives
        for (int i = 0; i < jobsCount; i++) {
            if (jobs[i].remaining_service_time == 0) continue;
            else if (jobs[i].arrival_time <= cpu->global_time) break;
            else  {
                runIdle(cpu, jobs[i].arrival_time - cpu->global_time);
                break;
            }
        }

        for (int i = 0; i < jobsCount; i++) {
            if (jobs[i].remaining_service_time > 0
                && jobs[i].arrival_time <= cpu->global_time) {
                if (next == NULL) next = &jobs[i];
                else if (next->remaining_service_time > jobs[i].remaining_service_time)
                    next = &jobs[i];
            }
        }

        assert(next != NULL);
        giveCPUJob(cpu, next);
        runCurrentJob(cpu, cpu->job->remaining_service_time);
        completed++;
    }
}
