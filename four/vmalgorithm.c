/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

/*
 *  Implementation of FIFO and LRU page replacement algorithm
 */

#include "vmalgorithm.h"



/* 
 * Generates a ramdom access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern() {
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("\nThe randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++) {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}



/*
 * Initializes the parameters of a simulated memory
 */
void initializePageFrame() {
    int i;
    
    // dynamic allocated FrameNR frames to be used in memory
    memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    
    
    memory.table = (int *)malloc( sizeof(int)* FrameNR ); //aux table
    
    memory.nextToReplaced = 0;  // indicate the new frame to be replaced as 0
   
   
    for(i=0; i< FrameNR; i++) {
        memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused
        memory.table[i] = 0; 
   }
}


/*
 * Prints all pages loaded in memory
 */
void printPageFrame() {
   int i;
   for(i=0; i< FrameNR; i++) {
        printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}



/*
 * Prints the access pattern again
 */
void printAccessPattern() {
   int i;
   printf("The Same Access Pattern: ");
   for(i=0; i < AccessPatternLength; i++) {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}



 /*
 * Return: number of pages fault using FIFO page replacement algorithm
 */
int FIFO() {

    int pageFaultCount=0;
    int i;
    
    for (i = 0; i < AccessPatternLength; i++) {
       pageFaultCount += FIFOInsert(accessPattern[i]);
       printPageFrame();
   }
   return pageFaultCount;
   
   
}


/*
 * Return: the page fault using FIFO page replacement algorithm
 */
int FIFOInsert(int pageNumber) {
    int pageFault = 0;
    
    if ( 0 == FIFOSearch(pageNumber) ) {

        memory.PageFrameList[memory.nextToReplaced] = pageNumber;
        memory.nextToReplaced = (memory.nextToReplaced + 1) % FrameNR;
        pageFault = 1;
    }

    return pageFault;      
}


/*
 * Search for the Page Number using FIFO
 */
int FIFOSearch(int pageNumber) {
    
    int i;
    for ( i = 0; i < FrameNR; i++ ) {
        
        if (memory.PageFrameList[i] == pageNumber) {
            return 1;
        }
    }
    return 0;
}



/*
 * Return: number of pages fault using LRU page replacement algorithm
 */
int LRU() {
    
    int pageFaultCount = 0;
    int i;

    for ( i = 0; i < AccessPatternLength; i++ ) { 
        pageFaultCount += LRUInsert(i);
        printPageFrame();
    }
    
    return pageFaultCount; 
}


/*
 * Return: the page fault using LRU page replacement algorithm
 */
int LRUInsert(int pageNumber) {
    
    int pageFault = 0;
    int findIndex = -1;
    
    findIndex = LRUSearch(pageNumber);

    if ( findIndex == -1 ) { 
        // replace page
        memory.PageFrameList[memory.nextToReplaced] = accessPattern[pageNumber];
        pageFault = 1;
    }
    
    return pageFault;
}


/*
 * Search for the Page Number using LRU
 */
int LRUSearch(int pageNumber) {

    int k;
    
    // reset table
    int i;
    for (i = 0; i < FrameNR; i++) {
        memory.table[i] = 0;      
    }


    for ( i = 0; i < FrameNR; i++) {
        // If the page is in the frame
        if (memory.PageFrameList[i] == accessPattern[pageNumber]) {
            return i;
        }
        
        // If the frame has the new page
        else if (memory.PageFrameList[i] == -1) {
            memory.nextToReplaced = i;
            return -1;
        }
        
        // If the frame is full AND doesn't have the new page
        else {
            // Find indices of the least recently used pages.
            for (k = pageNumber-1; k > 0; k--) {
                if (memory.PageFrameList[i] == accessPattern[k]) {
                    memory.table[i] = k;
                    break;
                }
            }
        }
    }
    
    
    // find the index of the least recently used page in the frame.
    int min = 9999;
    for ( i = 0; i < FrameNR; i++) {
        if (memory.table[i] < min) {
            min = memory.table[i];
            memory.nextToReplaced = i;
        }
    }
    
    return -1;
}

