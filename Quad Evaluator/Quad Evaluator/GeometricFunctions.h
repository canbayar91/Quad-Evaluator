#ifndef GEOMETRIC_FUNCTIONS
#define GEOMETRIC_FUNCTIONS

#include "Quadrilateral.h"

typedef Edge Vector;
typedef Edge Normal;
typedef double Angle;

#define PI 3.14159265

class GeometricFunctions {
public:
	
	// Calculates the dot product value of two vectors
	static double dotProduct(const Vector &a, const Vector &b);

	// Calculates the cross product value of two vectors
	static double crossProduct(const Vector &a, const Vector &b);

	// Checks whether a quadrilateral is concave or not
	static bool checkConcavity(const Quadrilateral &quadrilateral);

	// Finds the intersection point of two line segments
	const static Vertex findLineIntersection(const Edge &a, const Edge &b);

	// Calculates the normal vector of two vectors using the cross product
	const static Normal findNormal(const Vector &a, const Vector &b);

	// Calculates the angle between two vectors
	const static Angle calculateAngle(const Vector &a, const Vector &b);

	// Converts degrees to radians
	const static Angle degreesToRadians(const Angle angle);

	// Converts radians to degrees
	const static Angle radiansToDegrees(const Angle angle);

	// Normalizes the given vector to a unit vector
	const static Vector normalizeVector(const Vector &vector);

};

#endif
