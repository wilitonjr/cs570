/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/


/*
 * specialcharcount.c - this file implements the specialcharcount and printSpecialCharFrequencyIntoFile functions.
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "count.h"






/**
* Function to count the frequency of 5 special characters ( ','   '.'   ':'    ';'    '!' ) in all 
* .txt files under directory of the given path and calls the function to save 
* the results to a file named as filetowrite.
*  
* Inputs: 
*     path - a pointer to a char string [a character array] specifying the path of the 
*               directory.
*     filetowrite - a pointer to a char string [a character array] specifying the file where 
*                        results should be written in.
*     alphabetfreq - a pointer to a long array storing the frequency of the 5 special 
*                            characters given.
*      
* Output: 
*     A new file named as filetowrite with the frequency of the above special characters 
*     written in. Format: character -> frequency
*  
* Example:
*     , -> 20
*     . -> 11      
*/

void specialcharcount(char *path, char *filetowrite, long charfreq[])
{

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
                    count[c]+=1;   // add one to the count of the character
                }

                 fclose(fp); // closes file
                
            } 
        } 
        
        
        
        /*
        * Gets the total count of the specific special characters
        * we want  ( ','   '.'   ':'    ';'    '!' ) and transfers to the 'charfreq' list
        */
        for(k=33; k<60; k++) {
                if (count[k] > 0) {
                    
                    if ( k == 44 ){
                         charfreq[0] = count[k]; // ','
                    }
                    if ( k == 46 ){
                         charfreq[1] = count[k]; // '.'
                    }
                    if ( k == 58 ){
                         charfreq[2] = count[k]; // ':'
                    }
                    if ( k == 59 ){
                         charfreq[3] = count[k]; // ';'
                    }
                    if ( k == 33 ){
                         charfreq[4] = count[k]; // '!'
                    }
                }
            }
                
        
        (void) closedir (path_with_files); // closes dir
    } 
    
    
    printSpecialCharFrequencyIntoFile(charfreq, filetowrite); // calls function to print into file
}




 /*
* Function to print the frequency stored in array charfreq[] into the filetowrite
* designated file into the '/result' directory
*
* Input: 
*   charfreq - array having the frequency of the special characters
*   filetowrite - the file where the result should be saved on
*/     

void printSpecialCharFrequencyIntoFile(long charfreq[], char *filetowrite)
{	

    FILE *fileToPrintSpecialCharResult = fopen(filetowrite, "w"); 
    
	for(int i = 0; i < 5; i++)
	  {
	  	switch(i)
	  	{
	  		case 0:
	  			fprintf(fileToPrintSpecialCharResult, ", -> %d\n", charfreq[i]);
	  			break;
	  		case 1:
	  			fprintf(fileToPrintSpecialCharResult,". -> %d\n", charfreq[i]);
	  			break;
	  		case 2:
	  			fprintf(fileToPrintSpecialCharResult,": -> %d\n", charfreq[i]);
	  			break;
	  		case 3:
	  			fprintf(fileToPrintSpecialCharResult,"; -> %d\n", charfreq[i]);
	  			break;
	  		case 4:
	  			fprintf(fileToPrintSpecialCharResult,"! -> %d\n", charfreq[i]);
	  			break;
	  	}	  	
	  }
	  fclose(fileToPrintSpecialCharResult);
}


