#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
	float x;
	float y;
public:
	Position();
	~Position();
	float GetX()const;
	float GetY()const;
	void SetX(float x);
	void SetY(float y);
	void SetXY(float x, float y);

};
#endif // !POSITION_H
//Get
float Position::GetX()const				{ return this->x; }
float Position::GetY()const				{ return this->y; }
//Set
void Position::SetX(float x)			{ this->x = x; }
void Position::SetY(float y)			{ this->y = y; }
void Position::SetXY(float x, float y)  { this->x = x; this->y = y; }