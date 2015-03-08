/*
  Name: 	Program 1
  Class: 	EECS 3500 - 001
  Due: 		03/17/2015
  Description:	Program to read in an NFA and convert it to a DFA for output. 
*/ 

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

void ReadFile(string newLine[]);

/*
  Start Here.
*/
int main (int argCount, char *argValues[]) {
   string nfaTable [100][27] = {"empty"};
   string dfaTable [100][27] = {"empty"};
   string newLine[100];
   
   ReadFile(newLine);

   
   //for(unsigned int i = 0; i < newLine[1].length(); i++) {
   //   alphabet += .at(i);
   //}   

   return EXIT_SUCCESS;
}

/*
  Read in text file and sort input.
*/
void ReadFile(string newLine[]) {
   ifstream inFile;
   inFile.open("NFA.txt");
   unsigned int lineNum = 0;

   if (inFile.good()) {
      cout << "=======[NFA From File]=======" << endl;
      while (getline(inFile,newLine[lineNum])) {
         cout << newLine[lineNum] << endl;
         lineNum++;
      }
      cout << "=============================" << endl << endl;
      inFile.close();
   } else {
      cout << "Could not find file \"NFA.txt\" for input.\n";
      inFile.clear();
   }

   // List first four lines of input as their respective categories.
   cout << "# of States   [" << newLine[0] << "]\n";
   cout << "Alphabet      [" << newLine[1] << "]\n";
   cout << "Final States  [";
   
   cout << "Initial State [" << newLine[3] << "]\n";

   // Sort all state transitions into NFA table.
}
