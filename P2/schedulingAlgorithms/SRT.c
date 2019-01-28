# include <assert.h>
# include "../CPU.h"
# include "../Job.h"
# include "SJF.h"

void RunSRT(CPU *cpu, Job *jobs, unsigned jobsCount) {
    unsigned completed = 0;
    unsigned time_delta;

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

        // Retrieve next job to run
        for (int i = 0; i < jobsCount; i++) {
            if (jobs[i].remaining_service_time > 0
                && jobs[i].arrival_time <= cpu->global_time) {
                if (next == NULL) next = &jobs[i];
                else if (next->remaining_service_time > jobs[i].remaining_service_time)
                    next = &jobs[i];
            }
        }

        // Retrieve next arrival time
        time_delta = next->remaining_service_time;
        for (int i = 0; i < jobsCount; i++) {
            if (cpu->global_time < jobs[i].arrival_time) {
                time_delta = jobs[i].arrival_time - cpu->global_time;
                time_delta = time_delta < next->remaining_service_time
                    ? time_delta : next->remaining_service_time;
                break;
            }
        }

        assert(next != NULL);
        giveCPUJob(cpu, next);
        runCurrentJob(cpu, time_delta);
        if (next->remaining_service_time == 0) completed++;
    }
}
