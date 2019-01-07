#ifndef EVALUATION_FUNCTIONS
#define EVALUATION_FUNCTIONS

#include "Quadrilateral.h"
#include "GeometricFunctions.h"

enum AlignmentType {
	HORIZONTAL,
	VERTICAL
};

class EvaluationFunctions {
public:
	
	// Calculates the minimum scaled jacobian metric value for a given quadrilateral
	const static double calculateScaledJacobian(const Quadrilateral &quadrilateral);

	// Calculates the distortion amount for a given quadrilateral (Canaan)
	const static double calculateDistortion(const Quadrilateral &quadrilateral);

	// Calculates the distortion amount for a given quadrilateral (T-Base)
	const static double calculateDistortion2(const Quadrilateral &quadrilateral);

	// Calculates the maximum warpage amount for a given quadrilateral
	const static double calculateMaximumWarpage(const Quadrilateral &quadrilateral);

	// Calculates the aspect-ratio for a given quadrilateral
	const static double calculateAspectRatio(const Quadrilateral &quadrilateral);

private:

	// Calculates the determinant of the jacobian matrix
	const static double calculateJacobianDeterminant(const Edge &left, const Edge &right);

	// Calculates the warpage amount for a given quadrilateral on given diagonal
	const static double calculateWarpage(const Quadrilateral &quadrilateral, AlignmentType alignment);

	// Calculates the triangle distortion defined by Lee & Lo
	const static double calculateTriangleDistortion(const Vertex &a, const Vertex &b, const Vertex &c);

	// Calculates the average of the corner points in a quadrilateral
	const static Vertex calculateCornerAverage(const Quadrilateral &quadrilateral);

	// Calculates the average of the normals on corner points in a quadrilateral
	const static Normal calculateNormalAverage(const Quadrilateral &quadrilateral);

	// Aligns a triangle to the z=0 plane
	const static void alignTriangle(Edge &left, Edge &right);

	// Aligns a non-planar quadrilateral onto an average plane
	const static Quadrilateral alignQuadrilateral(const Quadrilateral &quadrilateral);

};

#endif
