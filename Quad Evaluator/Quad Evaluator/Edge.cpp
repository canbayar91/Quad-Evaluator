#include "Edge.h"
#include <cmath>

Edge::Edge(const Vertex &start, const Vertex &end) {
	this->start = start;
	this->end = end;
}

void Edge::setStart(const Vertex &start) {
	this->start = start;
}

void Edge::setEnd(const Vertex &end) {
	this->end = end;
}

const Vertex &Edge::getStart() const {
	return start;
}

const Vertex &Edge::getEnd() const {
	return end;
}

const double Edge::getLength() const {
	double componentX = pow(getLengthX(), 2);
	double componentY = pow(getLengthY(), 2);
	double componentZ = pow(getLengthZ(), 2);
	return sqrt(componentX + componentY + componentZ);
}

const double Edge::getProductX() const {
	return end.x - start.x;
}

const double Edge::getProductY() const {
	return end.y - start.y;
}

const double Edge::getProductZ() const {
	return end.z - start.z;
}

const double Edge::getLengthX() const {
	return abs(getProductX());
}

const double Edge::getLengthY() const {
	return abs(getProductY());
}

const double Edge::getLengthZ() const {
	return abs(getProductZ());
}
