- Author -
Wiliton Abreu Rodrigues - cssc2301
SDSU - CS570 (summer 20)
REDid: 824508185



- Descripton -
This program counts the frequency of each alphabet letter (A-Z, a-z) and five 
special characters ( '.', ',', ':', ';', '!' ) in all the .txt files under the 'data' directory.

It saves the result in two '.txt' files and also displays the results on screen.



- How it works -
The programs opens all .txt files stored into the given directory ( /data ) and runs through 
them counting all desired characters. It stores this counting in a list. 
After doing all the run it prints the result (format: char -> count) both on screen and 
on two .txt file in the '/result' directory. ( result.txt and specialresult.txt ).



- How to Run -
The following commands should be executed to run the programs:

make testalphabet	// to generate testalphabet executable file.
make testspecial	// to generate testspecial executable file. 
./testalphabet    	// to run the testalphabet program to count frequency of alphabet letters ( A-Z a-z ).
./testspecial         	// to run the testspecial program to count frequency of the specific special characters ( '.', ',', ':', ';', '!' ).



- Outputs -

The result of the both programs are displayed on the screen.
They also saves a .txt file into the '/result' directory with the same results that were displayed on screen.
The files  with results are 'result.txt' and 'resultspecial.txt' for the 'testalphabet' and the 'testspecial' programs respectively.
