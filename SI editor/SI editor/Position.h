#pragma once
#ifndef Position_H
#define Position_H

class Position {
public:
	Position();
	Position(int, int);
	void setX(int);
	void setY(int);
	int getX() const;
	int getY() const;
private:
	int mX;
	int mY;
};
#endif