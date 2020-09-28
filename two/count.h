/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

/* charcount.h - This header file include type definitions (including function prototypes) and macros 
   used for the programing assignment two.
*/

#include <stdio.h> 

#define ALPHABETSIZE 52     //The total number of alphabetical letter from A - Z  a - z (case sensitive)

void* alphabetCountFiles(void* p);

void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int numberOfThreads);

int countNumberofTxtFilesInAFolder(char[]);

void printAlphabetFrequencyIntoFile(long charfreq[], char *filetowrite);