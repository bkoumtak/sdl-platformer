#include "Vector2D.h"

Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

//dont want a copy of it, just read it so reference &
Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;
	//return the vector we got
	return *this;
}
Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

//const so to not change it by mistake
//friend so it can access the private members and is called v1+v2
Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	//just use the Add func we made
	return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

//?= functions
Vector2D& Vector2D::operator +=(const Vector2D& vec) {
	return this->Add(vec);
}
Vector2D& Vector2D::operator -=(const Vector2D& vec) {
	return this->Subtract(vec);
}
Vector2D& Vector2D::operator *=(const Vector2D& vec) {
	return this->Multiply(vec);
}
Vector2D& Vector2D::operator /=(const Vector2D& vec) {
	return this->Divide(vec);
}
Vector2D& Vector2D::operator*(const int &i) {
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	//will use endl in actually implementation
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}