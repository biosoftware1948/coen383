# Compiler
CC			= gcc

#Flags, Libraries and Includes
CFLAGS		= -g -Wall

# Target Binary program
PROG		= main

# Directories, Sources and Resources
SRC_DIR 	:=
SCHED_DIR	:= schedulingAlgorithms/
BUILD_DIR	:= obj/
TARGET_DIR	:=
SRC_EXT		:= c
OBJ_EXT		:= o

# Program Files
SOURCES 	= $(wildcard $(SRC_DIR)*.c)
SCHED_ALGS	= $(wildcard $(SRC_DIR)$(SCHED_DIR)*.c)
OBJS		= $(SOURCES: %.c = %.o) $(SCHED_ALGS: %.c = %.o)

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

clean:;		$(RM) -f $(PROG) core *.o
