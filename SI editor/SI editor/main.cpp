#include <iostream>
#include "Editor.h"
#include <conio.h>
using namespace std;

void main(int argc, const char* argv[])
{

    if (argc > 1) {
        Editor si(argv[1]);
        si.run();
    }
    else {
        cout << "Can't open... will exit" << endl;
        exit(2);
    }

}