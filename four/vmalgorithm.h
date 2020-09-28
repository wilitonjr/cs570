/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

/********************************************
 * Page Replacement Simulation: header file
 *******************************************/

#include <time.h> 
#include <stdio.h>
#include <stdlib.h>


/**************************************
 * The parameters of memory and disk pages 
 *
 * PageFrameList: The dynamically-allocated array representing memory pages
 * FrameNR: the number of page frames in memory
 * nextToReplaced: Point to the next page to be replaced
 *
 * accessPattern: The sequence of the demanding pages
 * AccessPatternLength: The length of the randomized access pattern
 * ReferenceSZ: the page number range of the access pattern
 *
 */

#define AccessPatternLength 20  // total number of memory access 

typedef struct
{
    int *PageFrameList;     // The dynamically-allocated array representing memory pages
    int *table;     
    int nextToReplaced;	    // point to the next frame to be replaced
}PageFrame;



/*
 * The following global variables will be used in the program, please understand each of them before starting your coding ... 
 */


int *accessPattern;        // memory access pattern, for example: 4 2 2 0 1   means will access the page 4, 2, 2, 0 and 1 one by one in order


int ReferenceSZ;           // range of pages to be accssed
int FrameNR;               // the number of page frames in memory

PageFrame memory;          // representing the memory



/* Algorithm Functions */

int FIFO();
int LRU();



/* Algorithm Sub - Functions */

int FIFOSearch(int pageNumber);
int FIFOInsert(int pageNumber);
int LRUSearch(int pageNumber);
int LRUInsert(int pageNumber);



