/*
* Wiliton Abreu Rodrigues                                  
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>       
#include <sys/types.h>  
#include <sys/wait.h>  


/*
 * This program executes two child processes in parallel.
 * Here the programs 'testalphabet'and 'testspecial'  
 * are being executed in parallel.         
 */
 
int main() {
    
    
    /*
    * Child processes  arguments
    */ 
    char *argsAlphabet [] = {"./testalphabet", NULL};
    char *argsSpecial [] = {"./testspecial", NULL};


     /*
    * Creates the two child processes  
    */ 
    pid_t child1_pid, child2_pid;
    (child1_pid = fork()) && (child2_pid = fork()); 


     /*
    * Executes the 1st child process program   
    */ 
    if (child1_pid == 0) {    // Child 1 code
        printf ("CHILD <PID: %d>: Process is executing testalphabet program!\n",getpid());
        execvp (argsAlphabet[0],argsAlphabet); 
        exit(1);
    } 
    

     /*
    * Executes the 2nd child process program   
    */ 
    else if (child2_pid == 0) {    // Child 2 code
        printf ("CHILD <PID: %d>: Process is executing testspecial program!\n",getpid());
        execvp (argsSpecial[0],argsSpecial);         
        exit(1);
    } 
    
    
    else {    // Parent code
    
        /*
        * Waits the two chiildren terminate to to print a message and
        * make the terminal prompt available again.   
        */ 
        child2_pid = wait(NULL);  
        printf ("CHILD <PID: %d>: Process has done with testspecial program! See the results above!\n", child2_pid);
        
        child1_pid = wait(NULL); 
        printf ("CHILD <PID: %d>: Process has done with testalphabet program! See the results above!\n", child1_pid);
        
//         printf("\nPARENT<PID: %d>: Both programs have terminated.\n\n",getpid());
    }
	return 0;
}







/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc ...
 
 Requirements:
 
 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"
    
 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"
    
 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each 
 process.
   
   
 The expected screen print out should be similar as follows:
 
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2861232
b -> 494472
... ...

CHILD <16741> process has done with testalphabet program !
 */
