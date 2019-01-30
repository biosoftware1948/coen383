# include <assert.h>
#include <stdbool.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "HPFNP.h"

static bool isComplete(Job *jobs, unsigned jobsCount) {
    for (int i = 0; i < jobsCount; i++) {
        if (jobs[i].finish_time == -1) return false;
    }
    return true;
}

static Job *getNextJob(
        CPU *cpu, Job **p1, Job **p2, Job **p3, Job **p4, int *c1, int *c2, int *c3, int *c4) {
    if (*c1 != 0) return p1[0];
    if (*c2 != 0) return p2[0];
    if (*c3 != 0) return p3[0];
    if (*c4 != 0) return p4[0];

    return NULL;
}

static void removeCompleted(
        Job **p1, Job **p2, Job **p3, Job **p4, int *c1, int *c2, int *c3, int *c4) {
    for (int i = 0; i < *c1; i++) {
        Job *job = p1[i];
        if (job->remaining_service_time == 0) {
            for (int j = i + 1; j < *c1; j++)
                p1[j - 1] = p1[j];
            *c1 = *c1 - 1;
        }
    }

    for (int i = 0; i < *c2; i++) {
        Job *job = p2[i];
        if (job->remaining_service_time == 0) {
            for (int j = i + 1; j < *c2; j++)
                p2[j - 1] = p2[j];
            *c2 = *c2 - 1;
        }
    }

    for (int i = 0; i < *c3; i++) {
        Job *job = p3[i];
        if (job->remaining_service_time == 0) {
            for (int j = i + 1; j < *c3; j++)
                p3[j - 1] = p3[j];
            *c3 = *c3 - 1;
        }
    }

    for (int i = 0; i < *c4; i++) {
        Job *job = p4[i];
        if (job->remaining_service_time == 0) {
            for (int j = i + 1; j < *c4; j++)
                p4[j - 1] = p4[j];
            *c4 = *c4 - 1;
        }
    }
}

static void addJobs(
        CPU *cpu, Job *jobs, unsigned jobsCount,
        Job **p1, Job **p2, Job **p3, Job **p4,
        int *c1, int *c2, int *c3, int *c4) {

    for (int i = 0; i < jobsCount; i++) {
        if (cpu->global_time < 100 && cpu->global_time == jobs[i].arrival_time) {
            if (jobs[i].priority == 1) {
                p1[*c1] = &jobs[i];
                *c1 = *c1 + 1;
            } if (jobs[i].priority == 2) {
                p2[*c2] = &jobs[i];
                *c2 = *c2 + 1;
            } if (jobs[i].priority == 3) {
                p3[*c3] = &jobs[i];
                *c3 = *c3 + 1;
            } if (jobs[i].priority == 4) {
                p4[*c4] = &jobs[i];
                *c4 = *c4 + 1;
            }
        }
    }
}

static bool incompleteJobs(Job **p1, Job **p2, Job **p3, Job **p4, int *c1, int *c2, int *c3, int *c4) {
    for (int i = 0; i < *c1; i++) {
        if (p1[i]->start_time != -1) return true;
    }

    for (int i = 0; i < *c2; i++) {
        if (p2[i]->start_time != -1) return true;
    }

    for (int i = 0; i < *c3; i++) {
        if (p3[i]->start_time != -1) return true;
    }

    for (int i = 0; i < *c4; i++) {
        if (p4[i]->start_time != -1) return true;
    }

    return false;
}

void RunHPFNP(CPU *cpu, Job *jobs, unsigned jobsCount, int output) {
    sort_by_arrival_time(jobs, jobsCount);

    Job **j1 = malloc(sizeof(Job *) * jobsCount);
    int *c1 = malloc(sizeof(int));
    Job **j2 = malloc(sizeof(Job *) * jobsCount);
    int *c2 = malloc(sizeof(int));
    Job **j3 = malloc(sizeof(Job *) * jobsCount);
    int *c3 = malloc(sizeof(int));
    Job **j4 = malloc(sizeof(Job *) * jobsCount);
    int *c4 = malloc(sizeof(int));
    *c1 = *c2 = *c3 = *c4 = 0;

    Job *running = NULL;
    while (incompleteJobs(j1, j2, j3, j4, c1, c2, c3, c4)
            || (cpu->global_time < 100 && !isComplete(jobs, jobsCount))) {
        // Add new jobs
        addJobs(cpu, jobs, jobsCount, j1, j2, j3, j4, c1, c2, c3, c4);

        // Get next job
        Job *next = getNextJob(cpu, j1, j2, j3, j4, c1, c2, c3, c4);

        if (next == NULL) runIdle(cpu, 1, output);
        else if (running != NULL) {
            runCurrentJob(cpu, 1, output);
            if (running->remaining_service_time == 0) running = NULL;
            removeCompleted(j1, j2, j3, j4, c1, c2, c3, c4);
        } else {
            running = next;
            giveCPUJob(cpu, next);
            runCurrentJob(cpu, 1, output);
            removeCompleted(j1, j2, j3, j4, c1, c2, c3, c4);
        }
    }
}
