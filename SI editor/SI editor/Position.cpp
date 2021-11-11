#include "Position.h"
#include <iostream>
#include <windows.h>

using namespace std;

Position::Position() { //default constructor 
	mX = 0;
	mY = 0;
}

Position::Position(int , int ) { //define x and y
	mX = 0;
	mY = 0;
}

void Position::setX(int x) { // set x
	mX = x;
}

void Position::setY(int y) { // set y
	mY = y;
}

int Position::getX () const { // get x
	return mX;
}

int Position::getY () const { // get y
	return mY;
}