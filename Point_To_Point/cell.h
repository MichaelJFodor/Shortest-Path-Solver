#pragma once
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
class cell
{
private:
	int x_;
	int y_;
	int val_;
	int coord_;
	bool isSource_;

public:
	// Constructors
	cell() 
	{}
	cell(bool isSource) :
		isSource_(isSource) 
	{}
	cell(int x, int y): 
		x_(x), y_(y) 
	{}
	cell(int x, int y, bool isSource):
		x_(x), y_(y), isSource_(isSource)
	{}
	~cell() {}

	// Getters
	int getX();
	int getY();
	int getVal();
	int getCoord();
	bool getSource();
	int extractX(int width);
	int extractY(int width);

	// Setters
	void setSource(bool isSource);
	void setCoord(int coord);
	void calculateCoord(const int width);
	void setVal(const int val);
	void setX(const int x);
	void setY(const int y);
	void setXY(const int x, const int y);

	// Overloads
	cell& operator = (const cell& a);
};





