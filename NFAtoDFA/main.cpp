//
//  main.cpp
//  NFAtoDFA
//
//  Created by Apple iMac on 3/4/15.
//  Copyright (c) 2015 Apple iMac. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream inputFile("/Users/iMac/Documents/Spring2015/Automata/inputFile.txt");
    vector<char> file;
    char character;
    int numStates;
    vector<char> alphabet;
    vector<int> acceptingStates;
    int numAcceptingStates;
    int initialState;
    //transitionss
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
    numStates = (file[0] - 48);                         // number of states
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
    numAcceptingStates = (file[i] - 48);                // number of accepting states
    i++;
    while(file[i] != '\n'){
        acceptingStates.push_back((file[i] - 48));      // vector of accepting states
        if(file[i] == '\n')
            break;
        i++;
    }
    for(int z = 0; z < acceptingStates.size(); z++){
        cout << acceptingStates[z];
    }
    cout << endl;
}
