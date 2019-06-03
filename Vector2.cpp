#include "windows.h"
#include "Vector2.h"
                            
Vector2::Vector2 (POINT p) 
	:	x_(p.x),
   	 	y_(p.y)
{}

Vector2::Vector2 ()
	:	x_(0),
		y_(0)
{}

bool Vector2::isIn (std::pair<Vector2, Vector2> range)
{
	if (((x_ >= range.first.x_ && x_ <= range.second.x_) || (x_ <= range.first.x_ && x_ >= range.second.x_)) &&
		((y_ >= range.first.y_ && y_ <= range.second.y_) || (y_ <= range.first.y_ && y_ >= range.second.y_)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector2 operator+ (const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

Vector2 operator- (const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

Vector2 operator* (const Vector2& v1, const double& d)
{
	return Vector2(v1.x_*d, v1.y_*d);
}

Vector2 operator* (const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x_ * v2.x_, v1.y_ * v2.y_);
}

Vector2 operator/ (const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x_ / v2.x_, v1.y_ / v2.y_);
}

bool operator== (const Vector2& v1, const Vector2& v2)
{
	if (v1.x_ == v2.x_ && v1.y_ == v2.y_) return true;
	else return false;
}

bool operator!= (const Vector2& v1, const Vector2& v2)
{
	if (v1.x_ == v2.x_ && v1.y_ == v2.y_) return false;
	else return true;
}

double operator~ (const Vector2& v)
{
	return sqrt(v.x_*v.x_ + v.y_*v.y_);
}