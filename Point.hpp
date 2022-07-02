#include <stdio.h>

template<typename T = int>
struct Point {
	T x, y;
	Point operator-(const Point& b) const {
		return Point{x - b.x, y - b.y};
	}
	Point operator+(const Point& b) const {
		return Point{x + b.x, y + b.y};
	}
	void operator-=(const Point& b) {
		*this = *this - b;
	}
	void operator+=(const Point& b) {
		*this = *this + b;
	}
	Point operator*(const Point& b) const {
		return Point{x * b.x, y * b.y};
	}
	Point operator/(const Point& b) const {
		return Point{x / b.x, y / b.y};
	}
	Point operator*=(const Point& b) {
		*this = *this * b;
	}
	Point operator/=(const Point& b) {
		*this = *this / b;
	}
};

template<typename T = int> T cross(Point<T> a, Point<T>& b) { return a.x * b.y - b.x * a.y; }
template<typename T = int> T dot(Point<T> a, Point<T> b) { return a.x * b.x + a.y * b.y; }
