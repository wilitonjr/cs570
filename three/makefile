# A Makefile for Program 3, CS570
#
# Wiliton Abreu Rodrigues 
# Edoras - cssc2301
# SDSU - CS570 (summer 2020)
# REDid: 824508185
#

PROGRAM = testbbuffer
CC = gcc
CFLAGS = -g -std=c99 

${PROGRAM}:	${PROGRAM}.o bbuffer.o
		${CC} -o ${PROGRAM} ${PROGRAM}.o bbuffer.o -lpthread -lm



clean:
		rm -f *.o ${PROGRAM}

${PROGRAM}.o bbuffer.o: bbuffer.h
