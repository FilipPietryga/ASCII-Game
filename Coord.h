#pragma once
class Coord
{
private:
	int _x, _y;
public:
	Coord();
	Coord(int x, int y);
	int x();
	int y();
	void dx(int dx);
	void dy(int dy);
	void set(int x, int y);
};

