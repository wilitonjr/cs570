- Author -
Wiliton Abreu Rodrigues - cssc2301
SDSU - CS570 (summer 20)
REDid: 824508185



- Description -

This program updates the previous program described below. It forks two child processes, 
running the two programs ('testalphabet' and 'testspecial') in parallel.



- Previous program description -

This program counts the frequency of each alphabet letter (A-Z, a-z) and five 
special characters ( '.', ',', ':', ';', '!' ) in all the .txt files under the 'data' directory.

It saves the result in two '.txt' files and also displays the results on screen.



- How it works -

It spawns two child processes, one runs 'testspecial' and the other runs 'testalphabet', 
using 'fork()' and 'execvp()'functions.

When a child process starts executing a program, it prints a message to the output screen 
showing which child process (with PID) is running this program (with program name). 

When one child process finishes it prints a message showing which process (with PID) is done. 
The messages matches the real execution orders.


The 'testspecial' and 'testalphabet' programs opens all .txt files stored into the given 
directory ( /data ) and runs through  them counting all desired characters. It stores 
this counting in a list. 
After doing all the run it prints the result (format: char -> count) both on screen and 
on two .txt file in the '/result' directory. ( result.txt and specialresult.txt ).



- How to Run -

The following commands should be executed to run the programs:

make		// to generate mulproc executable file.
./mulproc    	// to run the mulproc program. It will execute both previous 
                ('testalphabet' and 'testspecial') programs in parallel.



- Outputs -

The result of the both programs are displayed on the screen. But now with the information 
of when it started and finished (with the correspondent PIDs).

They save a .txt file into the '/result' directory with the same results that were displayed on screen.
The files  with results are 'result.txt' and 'resultspecial.txt' for the 'testalphabet' 
and the 'testspecial' programs respectively.



- Screen output example -

CHILD <PID: 16741> process is executing testalphabet program!   
CHILD <PID: 16742> process is executing testspecial program!   
, -> 745668   
. -> 798072   
... ...   
CHILD <PID: 16742> process has done with testspecial program! See the results above!   
a -> 2861232   
b -> 494472 
... ... 
CHILD <PID: 16741> process has done with testalphabet program! See the results above!

