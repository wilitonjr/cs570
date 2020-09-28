# A Makefile for Program 4, CS570
#
# Wiliton Abreu Rodrigues 
# Edoras - cssc2301
# SDSU - CS570 (summer 2020)
# REDid: 824508185
#

testvm: testvm.o vmalgorithm.o
	gcc testvm.o vmalgorithm.o -o testvm 

testvm.o vmalgorithm.o: vmalgorithm.h


clean:
	rm -f *.o testvm
