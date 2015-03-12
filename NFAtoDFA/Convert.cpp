/*
  Name: 	Program 1
  Class: 	EECS 3500 - 001
  Due: 		03/17/2015
  Description:	Program to read in an NFA and convert it to a DFA for output. 
*/ 

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void ReadFile(string newLine[], string nfaTable[][27]);
void Convert(string nfaTable[][27], string dfaTable[][27], string newLine[]);
void WriteFile(string newLine[]);

/*
  Start Here.
*/
int main (int argCount, char *argValues[]) {
   string nfaTable [100][27] = { };
   string dfaTable [100][27] = { };
   string newLine[100] = { };
   
   cout << "\nReading NFA File...\n";
   cout << "\n=====[NFA BEGIN]=====\n";
   ReadFile(newLine, nfaTable);
   cout << "======[NFA END]======\n";

   cout << "\nConverting to DFA...\n";
   cout << "\n=====[DFA BEGIN]=====\n";
   Convert(nfaTable, dfaTable, newLine);
   cout << "======[DFA END]======\n";

   cout << "\nWriting DFA File...\n";
   WriteFile(newLine);
   cout << "\nComplete!\n\n";

   return EXIT_SUCCESS;
}

/*
  Read in text file and sort input.
*/
void ReadFile(string newLine[], string nfaTable[][27]) {
   ifstream inFile;
   inFile.open("NFA.txt");
   string myToken[3];
   string getToken;
   unsigned int lineNum = 0;

   // Read and list each line from input file.
   if (inFile.good()) {
      while (getline(inFile,newLine[lineNum])) {
         cout << newLine[lineNum] << endl;
         lineNum++;
      }
      inFile.close();
   } else {
      cout << "Could not find file \"NFA.txt\" for input.\n";
      inFile.clear();
   }

   // Sort all state transitions into NFA table.
   for(unsigned int i = 4; newLine[i] != ""; i++) {
      stringstream ss(newLine[i]);
      for(unsigned int j = 0; getline(ss,getToken, ' '); j++) { 
         myToken[j] = getToken;
      }
      nfaTable[atoi(myToken[0].c_str())][(int)myToken[1].at(0)-97] += myToken[2] + " ";
   }
}

/*
  Convert NFA table to DFA table.
*/
void Convert(string nfaTable[][27], string dfaTable[][27], string newLine[]) {
//Test transition table
   for(unsigned int i = 0; i < 100; i++) {
      for(unsigned int j = 0; j < 27; j++) { 
         if (nfaTable[i][j] != "") {cout << i << " " << j+97 << " " << nfaTable[i][j] << endl;}
      }
   }
}

/*
  Write final results to text file.
*/
void WriteFile(string newLine[]) {
   ofstream outFile;
   outFile.open("DFA.txt");
   unsigned int lineNum = 0;

   while (newLine[lineNum] != "") {
      outFile << newLine[lineNum] + "\n";
      lineNum++;
   }
}
