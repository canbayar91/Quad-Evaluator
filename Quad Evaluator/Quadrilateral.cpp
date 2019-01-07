#include "Quadrilateral.h"

Quadrilateral::Quadrilateral() {
	vertices[0] = Vertex(0, 0, 0);
	vertices[1] = Vertex(0, 0, 0);
	vertices[2] = Vertex(0, 0, 0);
	vertices[3] = Vertex(0, 0, 0);
}

Quadrilateral::Quadrilateral(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d) {
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
	vertices[3] = d;
}

const Vertex &Quadrilateral::getVertexA() const {
	return vertices[0];
}

const Vertex &Quadrilateral::getVertexB() const {
	return vertices[1];
}

const Vertex &Quadrilateral::getVertexC() const {
	return vertices[2];
}

const Vertex &Quadrilateral::getVertexD() const {
	return vertices[3];
}
