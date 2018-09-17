#pragma once
#include <iostream>

//v1.add(vec) or v1 + v2 or v1 += v2

class Vector2D {

public:
	float x, y;

	Vector2D();
	Vector2D(float x, float y);

	//dont want a copy of it, just read it so reference &
	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	
	//const so to not change it by mistake
	//friend so it can access the private members and is called v1+v2
	friend Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2);

	Vector2D& operator +=(const Vector2D& vec);
	Vector2D& operator -=(const Vector2D& vec);
	Vector2D& operator *=(const Vector2D& vec);
	Vector2D& operator /=(const Vector2D& vec);

	Vector2D& operator*(const int &i);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};