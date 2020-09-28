#include "vmalgorithm.h"

int main(int argc, char* argv[]) {
    
    int testmode = 0;
 
    if( argc != 3 )
    {
        printf("Please type the command again, following the format as: ./testvm  <reference page range> <number of memory frames>\n");
        return -1;
    }

   
    ReferenceSZ = atoi(argv[1]);
    FrameNR = atoi(argv[2]);
    
    
    /**** If you need more self-testing, please:
    
      1) uncomment generateAccessPattern() - line 24
      2) comment out line 29 - line 43
     ****/
    
    generateAccessPattern();   // Please uncomment the following line for more self-testing
        
    /*
     * Please comment out the following five lines for more self-testing
     */
//     testmode = 1;
//     int pattern[20] = {5,2,2,0,4,6,4,4,1,3,4,5,0,4,5,6,2,0,0,1};
//     int pattern1[20] = {4, 3, 2, 3, 2, 1, 5, 6, 6, 4, 6, 1, 5, 2, 5, 6, 4, 4, 4, 2};
//     int pattern2[20] = {1, 5, 4, 0, 3, 0, 6, 4, 0, 1, 4, 3, 1, 4, 0, 4, 1, 5, 3, 2};
//     int pattern3[20] = {4, 2, 5, 6, 0, 6, 6, 2, 1, 5, 1, 2, 6, 5, 3, 2, 2, 3, 0, 2};
//     accessPattern = pattern3; // CHOOSE THE PATTERN HERE
//     ReferenceSZ = 7;
//     FrameNR = 3;
//     
//     printf("\nThe Access Pattern: ");
//     int i;
//     for (i=0; i < 20; i++) {
//         printf("%d ", accessPattern[i]);       
//     }
//     printf("\n");
    /**** end  - self testing *******************************************************/
   

   initializePageFrame();
   
   printf("Running program using FIFO algorithm ... ...\n");
   printf("page fault of FIFO: %d\n",FIFO());
   
   free(memory.PageFrameList);

   printf("\n");
   printf("\n");

   
   printAccessPattern();   // print the access pattern again ...

   initializePageFrame();
   printf("Running program using LRU algorithm ... ...\n");
   printf("page fault of LRU: %d\n", LRU());
   free(memory.PageFrameList);


   if (testmode == 0)
        free(accessPattern);	

   return 0;

}
