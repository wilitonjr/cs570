/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

/* count.h - This header file include type definitions (including function prototypes) and macros used for the programing assignment zero.
*/

#include <stdio.h> 

#define ALPHABETSIZE 52     //The total number of alphabetical letter from A - Z and a - z(case sensitive)
#define SPECIALCHARSIZE 5   // The number of these special characters ','   '.'  ';'  ':'  '!' 




void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);
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



void printAlphabetFrequencyIntoFile(long charfreq[], char *filetowrite);
 /*
* Function to print the frequency stored in array charfreq[] into the filetowrite
* designated file into the '/result' directory
*
* Input: 
*   charfreq - array having the frequency of the special characters
*   filetowrite - the file where the result should be saved on
*/ 



void specialcharcount(char *path, char *filetowrite,  long charfreq[]);
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



void printSpecialCharFrequencyIntoFile(long charfreq[], char *filetowrite);
 /*
* Function to print the frequency stored in array charfreq[] into the filetowrite
* designated file into the '/result' directory
*
* Input: 
*   charfreq - array having the frequency of the special characters
*   filetowrite - the file where the result should be saved on
*/ 


