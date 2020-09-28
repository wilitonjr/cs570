/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/



/*
* alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
*/

#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>alp
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include "count.h"

pthread_mutex_t lock; //Mutex initialized

typedef struct data{
    int firstFileIndex;
    int lastFileIndex;
    long* alphabetFrequency;
    char *path;
    int thread_num;
} data;



/*
* alphabetcountmulthreads function counts the frequency of each alphabet 
* letter (a-z, case insensitive) in all the .txt files under directory 
* of the given path and write the results to a file named as filetowrite. 
* The function uses mutithreading to speed the process up.
*  
* Inputs: 
*     path - a pointer to a char string [a character array] specifying 
*         he path of the directory.
*     filetowrite - a pointer to a char string [a character array] 
*         specifying the file where results should be written in.
*     alphabetfreq - a pointer to a long array storing the frequency of 
*         the letter characters given.
*      
* Output: 
*     A new file named as filetowrite with the frequency of the above special characters 
*     written in. Format: character -> frequency
*/
void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int numberOfThreads) {

    
    
    char pathBar [200];
    strcpy( pathBar, path ) ;   
    strcat( pathBar, "/" ) ;
    
    int numberOfTextFiles = countNumberofTxtFilesInAFolder(path);
    int filesPerThread = numberOfTextFiles / numberOfThreads;
    int extraFileThreads = numberOfTextFiles % numberOfThreads; 
    
    printf("\n# of threads: %d\n", numberOfThreads); 
    printf("# of text files: %d\n", numberOfTextFiles);
    printf("Files / Threads (base): %d\n", filesPerThread);
    printf("Threads with an extra file: %d\n\n", extraFileThreads);
    
    int currentIndex = 0;
    data thread_data[numberOfThreads];
    
    
    // Declare arguments for all threads
    for (int i = 0; i < numberOfThreads; i++){
        thread_data[i].firstFileIndex = currentIndex;
        thread_data[i].lastFileIndex = currentIndex + filesPerThread - 1;
        thread_data[i].path = pathBar;
        thread_data[i].alphabetFrequency = alphabetfreq;
        currentIndex += filesPerThread;
        if (i < extraFileThreads) {
            thread_data[i].lastFileIndex ++;
            currentIndex ++;
        } 
        thread_data[i].thread_num = i;
    }
    
    
    // Declare thread IDs
    pthread_t *tid = malloc(numberOfThreads * sizeof(pthread_t));
    
    // Start all threads
    for (int i = 0; i < numberOfThreads; i++){
        pthread_create(&tid[i], NULL, &alphabetCountFiles, &thread_data[i]);
    }
    
    // Wait untill threads are done
    for (int i = 0; i < numberOfThreads; i++){
        pthread_join(tid[i], NULL);
    }
    
    pthread_mutex_destroy(&lock); //mutex is destroyed
    
    printAlphabetFrequencyIntoFile(alphabetfreq, filetowrite); // calls function to print into file
    
    printf(" \n");
	
}





/*
* Function alphabetCountFiles - THREAD function
*
* Thread function to count the frequency of each alphabet letter in the 
* .txt files under the given path. 
*  
* # The multiple threads run in parallel to share the workload. If 3 
*   threads are created to process 30 files, then each thread process 10 files;
* # The array 'alphabetfreq' is always up-to-date. It always has the result 
*   of all the threads counted so far.  
* # The threads also use mutexes to protect the critical process to feed 
*   the final array.
*
* Inputs: 
*     args - a pointer to all argumenrts os the thread
*         firstFileIndex - First files the thread will process
*         lastFileIndex - Last files the thread will process
*         alphabetFrequency - A pointer to the array that needs to be updated
*         path - The directory where the .txt files are stored
*         thread_num - The number of the thread that is being in progress
*      
*/
void *alphabetCountFiles(void *args) {

    
    
    int lastDigitsThreadId = pthread_self() % 100000;    
    data* ptr = (data*)args;
    char c;
    FILE *file;
    int countCharacters[256] = { 0 };
    
    
    // print "Start" message
    printf ("Thread id = %li starts processing files with index from %d to %d!\n", lastDigitsThreadId, ptr->firstFileIndex, ptr->lastFileIndex); 
    
    
    /* 
    * FOR loop to run through all files this thread is responsible for.  
    */    
    for (int i = ptr->firstFileIndex; i <= ptr->lastFileIndex; i ++) {
        
        
        char fileNameWithPath [200];
        char fileName[99] = "input_";
        char fileNumber [2];
        
        
        // Treats the file name to read it and print it correctly 
        strcpy(fileNameWithPath, ptr->path);
        strcat( fileNameWithPath, "input_" ) ;
        if (i < 10) strcat( fileNameWithPath, "0" ) ;
        sprintf(fileNumber, "%d", i);
        strcat( fileNameWithPath, fileNumber ) ;
        strcat( fileNameWithPath, ".txt" ) ;
        if (i < 10) strcat( fileName, "0" ) ;
        strcat( fileName, fileNumber ) ;
        strcat( fileName, ".txt" ) ;
        
        // print "processing" message
        printf ("Thread id = %li is processing file %s\n", lastDigitsThreadId, fileName);
        file = fopen(fileNameWithPath, "r");

        // Read file
        if (file) {
            while ( c=fgetc(file) ) {
                if ( c == EOF ) break;
                countCharacters[c]+=1;
            }
            fclose(file);
        }
    }
    
    
    //Mutex locked to protect critical region 
    pthread_mutex_lock(&lock);
    
    // FOR loop to update the alphabetfreq array.
    for(int k=65; k<123; k++) {
        if (countCharacters[k] > 0) {
            if ( k > 64 && k < 91 ) {    // A-Z
                int m = k - 65;
                 ptr->alphabetFrequency[m] = ptr->alphabetFrequency[m] + countCharacters[k];
            }
            if ( k > 96 && k < 123 ) { // a-z
                int m = k - 71;
                 ptr->alphabetFrequency[m] = ptr->alphabetFrequency[m] + countCharacters[k];
            }
        }
    }
    
    
    //Mutex unlocked
    pthread_mutex_unlock(&lock);   
    
    
    // print "END message"
    printf("Thread id = %li is done!\n", lastDigitsThreadId);
    
    pthread_exit(NULL);
}



/*
* Function to print the frequency stored in array charfreq[] into the filetowrite
* designated file into the '/result' directory
*
* Input: 
*   charfreq - array having the frequency of the special characters
*   filetowrite - the file where the result should be saved on
*/ 
void printAlphabetFrequencyIntoFile(long charfreq[], char *filetowrite) {
    
    FILE *fileToPrintAlphabetResult = fopen(filetowrite, "w"); 
    
	for(int i = 0; i < 26; i++) {   // print upper case letter frequency into file	  
        fprintf(fileToPrintAlphabetResult, "%c -> %d\n", (char)(i+65), charfreq[i]);
    }

   	for(int i = 26; i < 52; i++) { // print lower case letter frequency into file
        fprintf(fileToPrintAlphabetResult,"%c -> %d\n", (char)(i+65 + 6), charfreq[i]);  
    }
	  
    fclose(fileToPrintAlphabetResult);
}



/*
* Function to get the number of .txt files in a given folder
* Input: 
*     path - a pointer to a char string [a character array] specifying the path of the 
*               directory.
* Output: 
*     numberOfTextFiles - An integer with the number of .txt files int he given folder
*/
int countNumberofTxtFilesInAFolder(char *path){

    struct dirent *folder;     
    DIR *pathWithFiles = opendir (path);
    
    int numberOfTextFiles = 0;

    if ( pathWithFiles != NULL ) {
        while ((folder = readdir (pathWithFiles)) != NULL) {   
            int length = strlen(folder -> d_name);   
            if ( strncmp(folder -> d_name + length - 4, ".txt", 4) == 0 ){       
                numberOfTextFiles ++;   // # of text files
            }
        }
    }
    closedir (pathWithFiles);
    return numberOfTextFiles;
}






/**
  The alphabetcountmulthreads function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite. Different with programming assignment#0, you need to implement the program using mutithreading.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z, which should be already up-to-date;
      num_threads - number of the threads running in parallel to process the files
      
       
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Requirements:
1)	Multiple threads are expected to run in parallel to share the workload, i.e. sufolderose 3 threads to process 30 files, then each thread should process 10 files;
2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
Thread id = 274237184 starts processing files with index from 0 to 10!
3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
Thread id = 265844480 is processing file input_11.txt
4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
      Thread id = 274237184 is done !
5)	The array: long alphabetfreq[ ] should always be up-to-date, i.e. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]


You should have the screen printing should be similar as follows:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  ??

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 a -> 2861232
 b -> 494472
 c -> 747252
 ? ?
*/
