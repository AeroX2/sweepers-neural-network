#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Vector
{
	public:
		Vector(double x=0, double y=0);

		Vector operator+(const Vector& rhs);
		Vector operator-(const Vector& rhs);
		Vector operator*(const Vector& rhs);
		Vector operator*(const float rhs);

		Vector& operator+=(const Vector& rhs);
		Vector& operator-=(const Vector& rhs);
		Vector& operator*=(const Vector& rhs);
		Vector& operator*=(const float rhs);

		float distance();
		float fake_distance();
		Vector normalise();
		void print();

		double x;
		double y;
};

#endif
