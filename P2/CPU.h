#include "Job.h"

typedef enum CPU_State {available, busy} CPU_State;

typedef struct CPU {
	CPU_State cpuState;
	Job job;
} CPU;

CPU* createCPU();

void giveCPUJob(CPU* cpu, Job job);

void freeCPU(CPU* cpu);