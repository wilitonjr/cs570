/*
 * alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

#define _SVID_SOURCE
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include "count.h"


typedef struct data{
    int firstFileIndex;
    int lastFileIndex;
    int numberOfFiles;
    char** filePaths;
    long* alphabetFrequency;
    int* arr;
    int thread_num;
} data;

int arrSize = 10; 


/*
* Function to get the number of .txt files in a given folder
*/
int countNumberofTxtFilesInAFolder(char *path){

    DIR *pathWithFiles;
    struct dirent *folder;     
    pathWithFiles = opendir (path);
    
    int numberOfTextFiles = 0;

    if ( pathWithFiles != NULL ) {
        while ((folder = readdir (pathWithFiles)) != NULL) {   
            int length = strlen(folder -> d_name);   
            if ( strncmp(folder -> d_name + length - 4, ".txt", 4) == 0 )       // if it is a .txt filetype              
                    numberOfTextFiles ++;   // # of text files
        }
    }
    
    closedir (pathWithFiles);
    return numberOfTextFiles;
}


/*
* Function alphabetCountFiles
*/
void *alphabetCountFiles(void *p) {
    
    data* ptr = (data*)p;
    int n = ptr->thread_num;
    
    
    // Declare sum dynamically to return to join:
    int* thread_sum = (int*) calloc(1, sizeof(int));
//     int* thread_count[] = (int*) calloc(1, sizeof(int));
    int thread_count[256] = { 0 };
    
    
     printf ("Thread id = %d starts processing files with index from %d to %d!\n", pthread_self(), ptr->firstFileIndex, ptr->lastFileIndex);
    
    
    char c;
    FILE *file;
    
    int count[256] = { 0 };
    
    for (int i = ptr->firstFileIndex; i <= ptr->lastFileIndex; i ++) {
        file = fopen(ptr->filePaths[i], "r");
        if (file) {
            while ( (c=fgetc(file)) ) {
                if ( c == EOF ) break;
                count[c]+=1;
            }
            fclose(file);
        }
    }
    for(int k=65; k<123; k++) {
        if (count[k] > 0) {
            if ( k > 64 && k < 91 ) {    // A-Z
                int m = k - 65;
                 ptr->alphabetFrequency[m] = count[k];
//                   thread_count[m] = count[k];
//                   alphabetfreq [m] = count[k];
            }
            if ( k > 96 && k < 123 ) { // a-z
                int m = k - 71;
                 ptr->alphabetFrequency[m] = count[k];
//                   thread_count[m] = count[k];
            }
        }
    }
    printf("Thread id = %d is done!\n", pthread_self());
    
    //prints the result of this thread only
    for (int i = 0; i < 4; i++) {
        //alphabetfreq[i] = alphabetfreq[i] +ptr->alphabetFrequency[i];
        printf("-- %c -> %d\n", (char)(i+65), ptr->alphabetFrequency[i]);
    }
    
    
    if(n == 0){
        for(int i = 0; i < arrSize/2; i++)
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
    }
    else{
        for(int i = arrSize/2; i < arrSize; i++)
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
    }
    
    
     pthread_exit(NULL);
}


void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int numberOfThreads) {

    int numberOfTextFiles = countNumberofTxtFilesInAFolder(path);
    
    
    DIR *pathWithFiles;
    struct dirent *folder;     
    pathWithFiles = opendir (path);
    
    
    
    
    // Declare integer array [1,2,3,4,5,6,7,8,9,10]:
    int* int_arr = (int*) calloc(arrSize, sizeof(int));
    for(int i = 0; i < arrSize; i++)
        int_arr[i] = i + 1;
        
    char *listOfFileNames[numberOfTextFiles]; // Array with all filenames
    
    
    int loop = 0;
    while (((folder = readdir (pathWithFiles)) != NULL) && (loop != numberOfTextFiles) ) {   
        int length = strlen(folder -> d_name);   
        if ( strncmp(folder -> d_name + length - 4, ".txt", 4) == 0 ){       // if it is a .txt filetype              
            char name_of_the_file [99];
            strcpy(name_of_the_file, folder -> d_name);
            
            char file_with_path[200] ;
            strcpy( file_with_path, path);
            strcat( file_with_path, "/" ) ;
            strcat( file_with_path, name_of_the_file);
            listOfFileNames[loop] = strdup(file_with_path);
            //printf("listOfFileNames[%d]: %s\n",loop, listOfFileNames[loop]);
            loop ++;
        }
    }
    closedir (pathWithFiles);
    
    int filesPerThread = numberOfTextFiles / numberOfThreads;
    int extraFileThreads = numberOfTextFiles % numberOfThreads; 
    
    printf("\n# of threads: %d\n", numberOfThreads); 
    printf("# of text files: %d\n", numberOfTextFiles);
    printf("Files / Threads (v1): %d\n", filesPerThread);
    printf("Threads with extra file: %d\n\n", extraFileThreads);

    int currentIndex = 0;
    
    
    
    
    

    
    // Declare arguments for both threads:
    data thread_data[numberOfThreads];
    
    for (int i = 0; i < numberOfThreads; i++){
        thread_data[i].firstFileIndex = currentIndex;
        thread_data[i].lastFileIndex = currentIndex + filesPerThread - 1;
        thread_data[i].numberOfFiles = numberOfTextFiles;
        thread_data[i].filePaths = listOfFileNames;
        thread_data[i].alphabetFrequency = alphabetfreq;
        currentIndex += filesPerThread;
        if (i < extraFileThreads) {
            thread_data[i].lastFileIndex ++;
            currentIndex ++;
        } 
        thread_data[i].thread_num = i;
        thread_data[i].arr = int_arr;
        
        
    }
    
    
    
    // Declare thread IDs:
    pthread_t *tid = malloc(numberOfThreads * sizeof(pthread_t));
    int *return_vals = malloc(numberOfThreads * sizeof(int));
//     pthread_t tid[numberOfThreads];
    
    
    // Start both threads:
    for (int i = 0; i < numberOfThreads; i++){
//         pthread_create(&tid[i], NULL, &foo, NULL);
        pthread_create(&tid[i], NULL, &alphabetCountFiles, &thread_data[i]);
//         pthread_create(&tid[i], NULL, alphabetCountFiles, &thread_data[i]);
        
    }
    
    
    
    
    // Declare space for sum:
    int* sum0;
    int* sum1;
    
    // wait untill finish work
    for (int i = 0; i < numberOfThreads; i++){
//         pthread_join(tid[i], NULL);
        pthread_join(tid[i], (void**) &return_vals[i]);
    }
    
     
	
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
