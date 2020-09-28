- Author -
Wiliton Abreu Rodrigues - cssc2301
SDSU - CS570 (summer 20)
REDid: 824508185



- Description -

This program updates the 'testalphabet' program described below. It uses multithreading to 
speedup the program process time.



- Previous program description -

This program counts the frequency of each alphabet letter (A-Z, a-z) in all the .txt files 
under the 'data' directory.

It saves the result in the 'result.txt' file and also displays the results on screen.



- How it works -

It creates multiple threads (number of threads defined by the user) to process the files


Each thread created will take care of a their part of the '.txt' files in the folder.


When a thread start to process files, it prints a message to the output screen 
showing that it started. 

It also shows messages at the moment it is processing each file

At the end, the thread shows a messaging saying it's done.

The messages matches the real execution orders.


The 'testmulthreads' programs opens all .txt files stored into the given 
directory ( /data ) and runs through  them counting all desired characters. It stores 
this counting in a list. 
After doing all the run it prints the result (format: char -> count) both on screen and 
on two .txt file in the '/result' directory. ( result.txt and specialresult.txt ).



- How to Run -

The following commands should be executed to run the programs:

make		// to generate testmulthreads executable file.
./testmulthreads N    	// to run the testmulthreads program. Where N is the number of threads 
					   that should be created. It will execute all threads in parallel.



- Outputs -

The result of the programs is displayed on the screen.

It also save a .txt file into the '/result' directory with the same results that were displayed on screen.
The files with results is 'result.txt'.



- Screen output example -

Please enter 2 arguments only eg."./testmulthreads #_of__threads!!"

# of threads: 3
# of text files: 31
Files / Threads (base): 10
Threads with an extra file: 1

Thread id = 6176 starts processing files with index from 0 to 10!
Thread id = 13472 starts processing files with index from 11 to 20!
Thread id = 13472 is processing file input_11.txt
Thread id = 20768 starts processing files with index from 21 to 30!
Thread id = 20768 is processing file input_21.txt
Thread id = 20768 is processing file input_22.txt
...
Thread id = 13472 is processing file input_20.txt
Thread id = 6176 is processing file input_08.txt
Thread id = 20768 is done!
Thread id = 13472 is done!
Thread id = 6176 is processing file input_09.txt
Thread id = 6176 is processing file input_10.txt
Thread id = 6176 is done!
 
The results are counted as follows : 
A -> 111804
B -> 62436
...
Z -> 0
a -> 2861232
b -> 494472
...
z -> 12936


