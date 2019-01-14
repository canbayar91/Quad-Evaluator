#include "Quadrilateral.h"

Quadrilateral::Quadrilateral() {
	this->a = Vertex(0, 0, 0);
	this->b = Vertex(0, 0, 0);
	this->c = Vertex(0, 0, 0);
	this->d = Vertex(0, 0, 0);
}

Quadrilateral::Quadrilateral(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Quadrilateral::Quadrilateral(const Quadrilateral& quadrilateral) {
	this->a = quadrilateral.a;
	this->b = quadrilateral.b;
	this->c = quadrilateral.c;
	this->d = quadrilateral.d;
}
