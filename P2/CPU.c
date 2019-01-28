#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CPU.h"
#include "Job.h"

CPU* createCPU() {
    CPU* cpu = malloc(sizeof(CPU));
    cpu->cpuState = available;

    return cpu;
}

void giveCPUJob(CPU* cpu, Job job) {
    cpu->job = job;
    cpu->cpuState = busy;
}

void freeCPU(CPU* cpu) {
    cpu->cpuState = available;
}