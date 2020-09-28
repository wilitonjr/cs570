/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/


/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "count.h"


/**
* Function to count the frequency of all letter characters ( A-Z a-z ) in all 
* .txt files under directory of the given path and calls the function to save 
* the results to a file named as filetowrite.
*  
* Inputs: 
*     path - a pointer to a char string [a character array] specifying the path of the 
*               directory.
*     filetowrite - a pointer to a char string [a character array] specifying the file where 
*                        results should be written in.
*     alphabetfreq - a pointer to a long array storing the frequency of the letter 
*                            characters given.
*      
* Output: 
*     A new file named as filetowrite with the frequency of the above special characters 
*     written in. Format: character -> frequency
*  
* Example:
*     A -> 20
*     ...
*     z -> 11      
*/

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]) {
	
    DIR *path_with_files;
    struct dirent *pp;     
    path_with_files = opendir (path);
    
    int count[256] = { 0 };
    int c;
    int k;

    if ( path_with_files != NULL ) {
        while ((pp = readdir (path_with_files)) != NULL) {                             
            int length = strlen(pp -> d_name); 
            if ( strncmp(pp -> d_name + length - 4, ".txt", 4) == 0 ) {                    
                            
                /*
                Gets the file name with the full path
                */
                char name_of_the_file [99];
                strcpy(name_of_the_file, pp -> d_name);
                
                char file_with_path[200] ;
                strcpy( file_with_path, path);
                strcat( file_with_path, "/" ) ;
                strcat( file_with_path, name_of_the_file);
                
                FILE *fp = fopen(file_with_path, "r");
                
                
               /*
                Character counter according to the ASCII table
                */ 
                while ( (c=fgetc(fp)) ) {
                    if( c == EOF ) break;  // stop when reachs the end of the file
                    count[c]+=1;  // add one to the count of the character
                }

                 fclose(fp);
                
            }  
        } 
        
        
        
        /*
        * Gets the total count of the specific special characters
        * we want (A-Z, a-z) and transfers to the 'alphabetfreq' list
        */
        int m;
        for(k=65; k<123; k++) {
            if (count[k] > 0) {
                if ( k > 64 && k < 91 ) {    // A-Z
                    m = k - 65;
                     alphabetfreq[m] = count[k];
                }
                if ( k > 96 && k < 123 ) { // a-z
                    m = k - 71;
                     alphabetfreq[m] = count[k];
                }
            }
        }
                

        (void) closedir (path_with_files);// closes dir
    } 
    
     printAlphabetFrequencyIntoFile(alphabetfreq, filetowrite); // calls function to print into file
}


 /*
* Function to print the frequency stored in array charfreq[] into the filetowrite
* designated file into the '/result' directory
*
* Input: 
*   charfreq - array having the frequency of the special characters
*   filetowrite - the file where the result should be saved on
*/ 

void printAlphabetFrequencyIntoFile(long charfreq[], char *filetowrite)
{
    
     FILE *fileToPrintAlphabetResult = fopen(filetowrite, "w"); 
    
	for(int i = 0; i < 26; i++)   // print upper case letter frequency into file
	  {
	  	fprintf(fileToPrintAlphabetResult, "%c -> %d\n", (char)(i+65), charfreq[i]);
	  }

       	for(int i = 26; i < 52; i++)  // print lower case letter frequency into file
	  {
	  	fprintf(fileToPrintAlphabetResult,"%c --> %d\n", (char)(i+65 + 6), charfreq[i]);  
	  }
	  
 	  fclose(fileToPrintAlphabetResult);
}


