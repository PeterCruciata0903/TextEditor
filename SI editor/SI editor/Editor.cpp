#include <iostream>
#include "Editor.h"
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h> //for placeCursorAt
#include "LinkedList.h"
#include "Position.h"
#include "ListInterface.h"
#include "PrecondViolatedExcep.h"

using namespace std;

Editor::Editor() { // Empty default constructor
}

void Editor::displayLines()
{
    int position;
    string nextLine, nextWord, line, word;
    system("cls");
    // goes through each line in the linked list 
    for (position = 1; position <= lines.getLength(); position++)
    {
        nextLine = lines.getEntry(position);

        int i = 0;
        while (i < nextLine.length()) {
            string word;
            // isolate a word at a time (can contain underscores)
            if (isalpha(nextLine[i])) {
                while (isalpha(nextLine[i]) || nextLine[i] == '_') {
                    word += nextLine[i];
                    i++;
                }
                if (binarySearch(keyWords, 0, NUMKEYWORDS - 1, word) != -1)  //found
                    colorText(1);
                else
                    colorText(0);
                cout << word;
            }

            else {
                colorText(0);
                cout << nextLine[i];
                i++;
            }

        }

        cout << endl;
    }
    placeCursorAt(cursorCoord);
} // end displayLines


void Editor::run() {
    Position cursorCoord; //calls default constructor and sets to (0,0)
    displayLines();
    placeCursorAt(cursorCoord);
    char userEntry;
    int currentLineNumber = 1;
    string currentLine;
    int currentPosition = 0;
    bool running = true; // conditon for continous while loop
    userEntry = _getch(); // user entry get ch

    while (running) { // begining of while loop

        if (userEntry == ':') { // if entry is :

            //move cursor to the desired position on screen
            cursorCoord.setX(0); // set x coord to 0, 0 is first position in txt file
            cursorCoord.setY(lineNumbers); //y= line numbers, line is set to first line
            placeCursorAt(cursorCoord);
            cout << userEntry;

            userEntry = _getche();

            if (userEntry == 'q') { // if user entry is q
                inFile.close(); // close program
                running = false; // close while loop 
            }

            else if (userEntry == 'w') { // if user entry is w
                inFile.close(); // close file resets coor positions
                inFile.open(fileName, ios::out); //open file
                for (int i = 1; i < lines.getLength(); i++) { // reads values from list and saves them
                    inFile << lines.getEntry(i) << endl;
                }
                inFile << lines.getEntry(lines.getLength());   // last value in the list
            }
            else {
                cout << "Your entry is not valid " << endl;
                exit(1);
            }
        }
        else if (userEntry == 'x') { // if entry is x
            currentLine = lines.getEntry(currentLineNumber); // current line number is 1
            currentLine.erase(currentPosition, 1); // current position is 0
            lines.replace(currentLineNumber, currentLine);
            system("cls"); // system clear
            displayLines();
            cursorCoord.setX(0); // sets coordinates to 0,0
            cursorCoord.setY(0);
            placeCursorAt(cursorCoord); // places cursor in default position
        }

        else if (userEntry == 'd') { // if user entry is d
            userEntry = _getch(); // get entry from user a second time
            if (userEntry == 'd') { // if user entry is d
                lines.remove(currentLineNumber); // removes current line, line 1
            }
            system("cls"); // clear screen
            displayLines(); // display line
        }


        if (userEntry != 'q') { // quits editor
            userEntry = _getch();
        }

    }//end of while
}// end of function

void placeCursorAt(Position coordinates) //place cursor at top of file 
{
    COORD coord;
    coord.X = coordinates.getX(); // gets position of dipsplay on x axis
    coord.Y = coordinates.getY(); // gets position of display on y axis
    SetConsoleCursorPosition( // sets standard console to desired position in read file
        GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

Editor::Editor(string nameOfFile) { // calls function Editor of class Editor of type string fileName
    string line; // string variable 
    fstream fileName; // fstream of file name
    this->fileName = nameOfFile; //ptr fileName pointing to nameOfFile
    inFile.open(nameOfFile); // opens allocated nameOfFile
    //check if file is open or not
    if (!inFile.is_open()) {
        cout << "File does not exist" << endl;
        cout << "Please check if the file name is correct" << endl;
    }
    //if open then copies data
    while (!inFile.eof()) {
        getline(inFile, line);
        lines.insert(currentLine, line);
        currentLine++;
    }

    inFile2.open("keyword.txt"); // opens Keyword file

    if (!inFile2.is_open()) { // inFile2 open checker
        cout << "File does not exist" << endl;
        cout << "Please check if the file name is correct" << endl;
    }
    if (inFile2.is_open()) { //reads in array
        for (int i = 0; i < 60; i++) {
            inFile2 >> keyWords[i];
        }
    }
}

int binarySearch(const string anArray[], int first, int last, string target)
{
    int index;
    if (first > last)
        index = -1; // target not in original array
    else
    {
        // If target is in anArray,
        // anArray[first] <= target <= anArray[last]
        int mid = first + (last - first) / 2;
        if (target == anArray[mid])
            index = mid; // target found at anArray[mid]
        else if (target < anArray[mid])
            // Point X
            index = binarySearch(anArray, first, mid - 1, target);
        else
            // Point Y
            index = binarySearch(anArray, mid + 1, last, target);
    } // end if
    return index;
} // end binarySearch

void colorText(int value)
{
    COORD coord;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, value + 240);
}//end colorText
