#ifndef QUADRILATERAL
#define QUADRILATERAL

#include "Edge.h"

const int POINT_COUNT = 4;

class Quadrilateral {
public:

	Quadrilateral();
	Quadrilateral(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d);

	const Vertex &getVertexA() const;
	const Vertex &getVertexB() const;
	const Vertex &getVertexC() const;
	const Vertex &getVertexD() const;

private:

	Vertex vertices[POINT_COUNT];

};

#endif
