#include "Triangle.h"

Triangle::Triangle() {
	this->a = Vertex(0, 0, 0);
	this->b = Vertex(0, 0, 0);
	this->c = Vertex(0, 0, 0);
}

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Triangle::Triangle(const Triangle& triangle) {
	this->a = triangle.a;
	this->b = triangle.b;
	this->c = triangle.c;
}
