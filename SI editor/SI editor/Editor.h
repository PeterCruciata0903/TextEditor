#pragma once
#include "Position.h"
#include <string>
#include "LinkedList.h"
#include <fstream>
#include <windows.h>

using namespace std;

const int NUMKEYWORDS = 60; // const int for number of words
// Function Protoypes 
void colorText(int value); 
int binarySearch(string anArray[], int first, int last, string target);
void placeCursorAt(Position coordinates); // place cursor function

class Editor {
private:
    LinkedList<string> lines; //Decalaring Linked List Variable
    string fileName;    // string variable 
    fstream inFile;    // file stream variable
    fstream inFile2; // Keyword.txt variable
    int lineNumbers = 20; // int variable to determine number of lines in read file
    int currentLine = 1; // variable determining line number as first line
    string keyWords[NUMKEYWORDS]; // string variable adding array keyWords with const of 60 words
    Position cursorCoord;
public:
    Editor(); // Default Constructor
    Editor(string fileName); // Editor Class with type string argument fileName
    void displayLines(); // void display lines function
    void run(); // run function 
};