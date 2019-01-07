#include "GeometricFunctions.h"
#include <cmath>

double GeometricFunctions::dotProduct(const Vector &a, const Vector &b) {

	// Calculate and return the dot product value
	return a.getProductX() * b.getProductX() + a.getProductY() * b.getProductY() + a.getProductZ() * b.getProductZ();
}

double GeometricFunctions::crossProduct(const Vector &a, const Vector &b) {

	// Calculate and return the cross product value
	double positivePart = a.getProductY() * b.getProductZ() + a.getProductZ() * b.getProductX() + a.getProductX() * b.getProductY();
	double negativePart = a.getProductZ() * b.getProductY() + a.getProductX() * b.getProductZ() + a.getProductY() * b.getProductX();
	return positivePart - negativePart;
}

bool GeometricFunctions::checkConcavity(const Quadrilateral &quadrilateral) {

	// There are two possible approaches to check concavity
	// 1 - Get the diagonals and see if they cross each other
	// 2 - Traverse through angles and see if any of them is bigger than 180
	// Second approach is used in this function, but non-planarity is a problem

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Get the edge vectors for the first vertex
	const Vector AB(vertexA, vertexB);
	const Vector AD(vertexA, vertexD);

	// Calculate the angle between vectors and return true if the angle > 180
	if (GeometricFunctions::calculateAngle(AB, AD) > 180.0) {
		return true;
	}

	// Get the edge vectors for the second vertex
	const Vector BC(vertexB, vertexC);
	const Vector BA(vertexB, vertexA);

	// Calculate the angle between vectors and return true if the angle > 180
	if (GeometricFunctions::calculateAngle(BC, BA) > 180.0) {
		return true;
	}

	// Get the edge vectors for the third vertex
	const Vector CD(vertexC, vertexD);
	const Vector CB(vertexC, vertexB);

	// Calculate the angle between vectors and return true if the angle > 180
	if (GeometricFunctions::calculateAngle(CD, CB) > 180.0) {
		return true;
	}

	// Get the edge vectors for the fourth vertex
	const Vector DA(vertexD, vertexA);
	const Vector DC(vertexD, vertexC);

	// Calculate the angle between vectors and return true if the angle > 180
	if (GeometricFunctions::calculateAngle(DA, DC) > 180.0) {
		return true;
	}

	// Return false, if the quadrilateral is convex
	return false;
}

const Vertex GeometricFunctions::findLineIntersection(const Edge &a, const Edge &b) {

	// Edge A is represented as a1x + b1y = c1
	double a1 = a.getEnd().y - a.getStart().y;
	double b1 = a.getStart().x - a.getEnd().x;
	double c1 = a1 * a.getStart().x + b1 * a.getStart().y;

	// Edge B is represented as a2x + b2y = c2
	double a2 = b.getEnd().y - b.getStart().y;
	double b2 = b.getStart().x - b.getEnd().x;
	double c2 = a2 * b.getStart().x + b2 * b.getStart().y;

	// Find the intersection point
	double determinant = a1 * b2 - a2 * b1;
	double x = (b2 * c1 - b1 * c2) / determinant;
	double y = (a1 * c2 - a2 * c1) / determinant;

	// Return the intersection point
	return Vertex(x, y);
}

const Normal GeometricFunctions::findNormal(const Vector &a, const Vector &b) {

	// Find the length of the normal vector in xyz-coordinates
	// TODO - Cross product can return 0
	double x = a.getProductY() * b.getProductZ() - a.getProductZ() * b.getProductY();
	double y = a.getProductZ() * b.getProductX() - a.getProductX() * b.getProductZ();
	double z = a.getProductX() * b.getProductY() - a.getProductY() * b.getProductX();

	// Add the vector lengths into the starting point
	Vertex endpoint(a.getStart().x + x, a.getStart().y + y, a.getStart().z + z);

	// Create the normal vector
	Normal normal(a.getStart(), endpoint);

	// Return the normal vector
	return normal;
}

const Angle GeometricFunctions::calculateAngle(const Vector &a, const Vector &b) {

	// Calculate the dot product
	double dotProduct = GeometricFunctions::dotProduct(a, b);

	// Get the lengths of the edges
	double lengthA = a.getLength();
	double lengthB = b.getLength();

	// Calculate the angle between the edges in degrees
	Angle angle = acos(dotProduct / (lengthA * lengthB)) * 180.0 / PI;

	// Return the angle
	return angle;
}

const Angle GeometricFunctions::degreesToRadians(const Angle angle) {

	// Convert degrees to radians
	return angle * PI / 180.0;
}

const Angle GeometricFunctions::radiansToDegrees(const Angle angle) {

	// Convert radians to degrees
	return angle * 180.0 / PI;
}

const Vector GeometricFunctions::normalizeVector(const Vector &vector) {

	// Get the length of the vector
	double length = vector.getLength();

	// Calculate the normalized vector endpoints
	double x = vector.getStart().x + vector.getLengthX() / length;
	double y = vector.getStart().y + vector.getLengthY() / length;
	double z = vector.getStart().z + vector.getLengthZ() / length;
	
	// Create and return the normalized vector
	return Vector(vector.getStart(), Vertex(x, y, z));
}
