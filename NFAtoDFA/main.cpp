//NFA to DFA program

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

int main(){
    ifstream inputFile("./inputFile.txt");
	if(!inputFile.is_open()) {
		cout << "Error opening file";
	}
    vector<char> file;
    char character;
    int numStates;
    vector<char> alphabet;
    vector<int> acceptingStates;
    int numAcceptingStates;
    int initialState;
    //transitions
	vector<tuple<int, char, int>> transitions;
    int lineNumber = 1;

    do{
        inputFile.get(character);
        file.push_back(character);
    } while(!inputFile.eof());
    file.pop_back();
    for(int x = 0; x < file.size(); x++){
        cout << file[x];
    }
    cout << endl;
    int i = 0;
    numStates = (file[0] - 48);                         // number of states, subtracting 48 to get correct int
    i = i + 2;
    while(file[i] != '\n'){                             // vector of alphabet
        alphabet.push_back(file[i]);
        i++;
        if(file[i] == '\n')
            break;
    }
    i++;
    for(int y = 0; y < alphabet.size(); y++){
        cout << alphabet[y];
    }
    cout << endl;
    numAcceptingStates = (file[i] - 48);                // number of accepting states, subtracting 48 to get correct int
    i = i + 2;
    while(file[i] != '\n'){
	if(file[i] == 0x20){				// space hex value = 0x20 
		i++;
		continue;
	}
        acceptingStates.push_back((file[i] - 48));      // vector of accepting states, subtracting 48 to get correct int
        if(file[i] == '\n')
            break;
        i++;
    }
	i++;
    for(int z = 0; z < acceptingStates.size(); z++){
        cout << acceptingStates[z];
    }
    cout << endl;
    initialState = (file[i] - 48);			// initial state number,  subtracting 48 to get correct int
    i = i + 2;
    while(i < file.size()){				// state transitions, subtracting 48 to get correct int 
	tuple<int, char, int> transition ((file[i] - 48), file[i + 2], (file[i + 4] - 48)); //
	i = i + 6;
	transitions.push_back(transition);
	if(i >= file.size())
		break;
    }
}
