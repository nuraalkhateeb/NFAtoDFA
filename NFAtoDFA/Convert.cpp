/*
  Name: 	Program 1
  By:		Noor Alkhateeb
                Cameron Seidl
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
   if(inFile.good()) {
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

   // Clean up newLine array for future DFA transitions.
   for(unsigned int i = 4; newLine[i] != ""; i++) { 
      newLine[i] = "";
   }
}

/*
  Convert NFA table to DFA table.
*/
void Convert(string nfaTable[][27], string dfaTable[][27], string newLine[]) {
   string myNode[100] = {"0 "};
   string myToken[100];
   string nfaFinStates[20];
   string getToken;
   unsigned int lineNum = 4;
   unsigned int finNum = 0;
   bool uniqueNode;

   // Copy row one from NFA table to DFA table.
   for(unsigned int i = 0; i < 27; i++) { 
      dfaTable[0][i] = nfaTable[0][i];
   }

   // Fill in the rest of the DFA table and count nodes.
   for(unsigned int i = 0; myNode[i] != ""; i++) {

      // Find unique results from current DFA table node.
      for(unsigned int j = 0; j < 27; j++) {
         uniqueNode = true;
         for(unsigned int k = 0; k < 100; k++) { 
            if(dfaTable[i][j] == myNode[k]) {uniqueNode = false;} 
            if(uniqueNode && (myNode[k] == "")) {
               myNode[k] = dfaTable[i][j];
               uniqueNode = false;
            }
         }
      }
      // Calculate results for next DFA node in table.
      if(myNode[i+1] != "") {
         stringstream ss(myNode[i+1]);
         for(unsigned int l = 0; getline(ss,getToken, ' '); l++) { 
            myToken[l] = getToken;
         }
         for(unsigned int m = 0; myToken[m] != ""; m++) { 
            for(unsigned int n = 0; n < 27; n++) {
               if(nfaTable[atoi(myToken[m].c_str())][n] != "") {
                  if(dfaTable[i+1][n].find(nfaTable[atoi(myToken[m].c_str())][n]) == string::npos) {
                     dfaTable[i+1][n] += nfaTable[atoi(myToken[m].c_str())][n];
                  }
               }
            }
         }
      }
      // Count total nodes for output.
      newLine[0] = to_string(i+1);
   }

   // Count and label finishing states.
   stringstream ss(newLine[2]);
   for(unsigned int i = 0; getline(ss,getToken, ' '); i++) { 
      nfaFinStates[i] = getToken;
   }
   newLine[2] = "";
   for(unsigned int i = 1; nfaFinStates[i] != ""; i++) { 
      for(unsigned int j = 0; myNode[j] != ""; j++) {
         if(myNode[j].find(nfaFinStates[i]) != string::npos) {
            newLine[2] += to_string(j) + " ";
            finNum++;
         }
      }
   }
   newLine[2] = to_string(finNum) + " " + newLine[2];

   // Re-label nodes for DFA table clean up.
   for(unsigned int i = 1; myNode[i] != ""; i++) { 
      for(unsigned int j = 0; j < 100; j++) {
         for(unsigned int k = 0; k < 27; k++) { 
            if(dfaTable[j][k] == myNode[i]) {dfaTable[j][k] = to_string(i);}
         }
      }
   }
   // Send DFA table to newLine for output.
   for(unsigned int i = 0; i < 100; i++) {
      for(unsigned int j = 0; j < 27; j++) { 
         if(dfaTable[i][j] != "") {
            newLine[lineNum] = to_string(i) + " " + (char)(j+97) + " " + dfaTable[i][j];
            lineNum++;
         }
      }
   }
   // Print DFA output.
   for(unsigned int i = 0; newLine[i] != ""; i++) { 
      cout << newLine[i] << endl;
   }
}

/*
  Write final results to text file.
*/
void WriteFile(string newLine[]) {
   ofstream outFile;
   outFile.open("DFA.txt");
   unsigned int lineNum = 0;

   while(newLine[lineNum] != "") {
      outFile << newLine[lineNum] + "\n";
      lineNum++;
   }
}
