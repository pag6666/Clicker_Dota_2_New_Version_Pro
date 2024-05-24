#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <string>
#include <vector>
struct PointF
{
	
private:
	int _x;
	int _y;
public:
	PointF() 
	{
		_x = -1;
		_y = -1;
	}
	PointF(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	int GetX() { return _x; }
	int GetY() { return _y; }
};
enum SideBot
{
	null = 0,
	dark = 6,
	light = 7
};
enum statePoint
{
	bottom = 2,
	top = 0,
	midd = 1,
	null_st = 9
};