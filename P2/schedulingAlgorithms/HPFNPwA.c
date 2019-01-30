# include <assert.h>
#include <stdbool.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "HPFNPwA.h"

static bool isComplete(Job *jobs, unsigned jobsCount) {
    for (int i = 0; i < jobsCount; i++) {
        if (jobs[i].finish_time == -1) return false;
    }
    return true;
}

static Job *getNextJob(
        CPU *cpu, struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    if (!isEmpty(p1)) return getFrontQueueElement(p1);
    if (!isEmpty(p2)) return getFrontQueueElement(p2);
    if (!isEmpty(p3)) return getFrontQueueElement(p3);
    if (!isEmpty(p4)) return getFrontQueueElement(p4);

    return NULL;
}

static void removeCompleted(
        struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    if (!isEmpty(p1) && getFrontQueueElement(p1)->remaining_service_time == 0) deQueue(p1);
    else if (!isEmpty(p2) && getFrontQueueElement(p2)->remaining_service_time == 0) deQueue(p2);
    else if (!isEmpty(p3) && getFrontQueueElement(p3)->remaining_service_time == 0) deQueue(p3);
    else if (!isEmpty(p4) && getFrontQueueElement(p4)->remaining_service_time == 0) deQueue(p4);
    return;
}

static void age(CPU *cpu, Job *jobs, int jobsCount) {
    for (int i = 0; i < jobsCount; i++) {
        if (cpu->global_time < jobs[i].arrival_time) break;
        jobs[i].age++;
    }
}

static void upgrade(
        struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {

    for (int i = 0; i < getQueueSize(p4); i++) {
        Job *j = getElement(p4, i);

        if (j->finish_time == -1 && j->age >= 5) {
            removeElement(p4, i);
            enQueue(p3, j);
            j->age = 0;
        }
    }

    for (int i = 0; i < getQueueSize(p3); i++) {
        Job *j = getElement(p3, i);

        if (j->finish_time == -1 && j->age >= 5) {
            removeElement(p3, i);
            enQueue(p2, j);
            j->age = 0;
        }
    }

    for (int i = 0; i < getQueueSize(p2); i++) {
        Job *j = getElement(p2, i);

        if (j->finish_time == -1 && j->age >= 5) {
            removeElement(p2, i);
            enQueue(p1, j);
            j->age = 0;
        }
    }
}

static void addJobs(
        CPU *cpu, Job *jobs, unsigned jobsCount,
        struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    for (int i = 0; i < jobsCount; i++) {
        if (cpu->global_time == jobs[i].arrival_time) {
            if (jobs[i].priority == 1) enQueue(p1, &jobs[i]);
            if (jobs[i].priority == 2) enQueue(p1, &jobs[i]);
            if (jobs[i].priority == 3) enQueue(p1, &jobs[i]);
            if (jobs[i].priority == 4) enQueue(p1, &jobs[i]);
        }
    }
}

void RunHPFNPwA(CPU *cpu, Job *jobs, unsigned jobsCount, int output) {
    sort_by_arrival_time(jobs, jobsCount);

    Queue *priority1 = createQueue();
    Queue *priority2 = createQueue();
    Queue *priority3 = createQueue();
    Queue *priority4 = createQueue();

    Job *running = NULL;

    while (cpu->global_time < 100 && !isComplete(jobs, jobsCount)) {
        // Add new jobs
        addJobs(cpu, jobs, jobsCount, priority1, priority2, priority3, priority4);

        // Get next job
        Job *next = getNextJob(cpu, priority1, priority2, priority3, priority4);

        if (next == NULL) runIdle(cpu, 1, output);
        else if (running != NULL) {
            age(cpu, jobs, jobsCount);
            runCurrentJob(cpu, 1, output);
            upgrade(priority1, priority2, priority3, priority4);
            if (running->remaining_service_time == 0) running = NULL;
            removeCompleted(priority1, priority2, priority3, priority4);
        } else {
            running = next;
            giveCPUJob(cpu, next);
            age(cpu, jobs, jobsCount);
            runCurrentJob(cpu, 1, output);
            upgrade(priority1, priority2, priority3, priority4);
            removeCompleted(priority1, priority2, priority3, priority4);
        }
    }
}
