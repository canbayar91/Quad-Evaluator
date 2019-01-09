#include "EvaluationFunctions.h"
#include <functional>
#include <algorithm>
#include <cmath>

const double EvaluationFunctions::calculateScaledJacobian(const Quadrilateral &quadrilateral) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Get the edge vectors for the first vertex
	Vector AB(vertexA, vertexB);
	Vector AD(vertexA, vertexD);

	// Project the triangle area created by the edge vectors to the z=0 plane
	projectTriangle(AB, AD);

	// Calculate the scaled jacobian value
	double minimum = calculateJacobianDeterminant(AD, AB) / AB.getLength() / AD.getLength();

	// Get the edge vectors for the second vertex
	Vector BC(vertexB, vertexC);
	Vector BA(vertexB, vertexA);

	// Project the triangle area created by the edge vectors to the z=0 plane
	projectTriangle(BC, BA);

	// Calculate the scaled jacobian value
	double scaledJacobian = calculateJacobianDeterminant(BA, BC) / BC.getLength() / BA.getLength();

	// Update the minimum scaled jacobian value, if it is less than the current one
	if (scaledJacobian < minimum) {
		minimum = scaledJacobian;
	}

	// Get the edge vectors for the third vertex
	Vector CD(vertexC, vertexD);
	Vector CB(vertexC, vertexB);

	// Project the triangle area created by the edge vectors to the z=0 plane
	projectTriangle(CD, CB);

	// Calculate the scaled jacobian value
	scaledJacobian = calculateJacobianDeterminant(CB, CD) / CD.getLength() / CB.getLength();

	// Update the minimum scaled jacobian value, if it is less than the current one
	if (scaledJacobian < minimum) {
		minimum = scaledJacobian;
	}

	// Get the edge vectors for the fourth vertex
	Vector DA(vertexD, vertexA);
	Vector DC(vertexD, vertexC);

	// Project the triangle area created by the edge vectors to the z=0 plane
	projectTriangle(DA, DC);

	// Calculate the scaled jacobian value
	scaledJacobian = calculateJacobianDeterminant(DC, DA) / DA.getLength() / DC.getLength();

	// Update the minimum scaled jacobian value, if it is less than the current one
	if (scaledJacobian < minimum) {
		minimum = scaledJacobian;
	}

	// Return the minimum scaled jacobian value
	return minimum;
}

const double EvaluationFunctions::calculateDistortion(const Quadrilateral &quadrilateral) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Get the diagonals on the quadrilateral
	const Vector diagonalAC(vertexA, vertexC);
	const Vector diagonalBD(vertexB, vertexD);

	// Find the intersection point of the diagonals
	// TODO - Diagonals of the concave quadrilaterals do not intersect
	const Vertex intersection = GeometricFunctions::findLineIntersection(diagonalAC, diagonalBD);

	// Calculate the triangle distortion amounts
	double alphaValues[POINT_COUNT];
	alphaValues[0] = calculateTriangleDistortion(vertexA, vertexB, intersection);
	alphaValues[1] = calculateTriangleDistortion(vertexB, vertexC, intersection);
	alphaValues[2] = calculateTriangleDistortion(vertexC, vertexD, intersection);
	alphaValues[3] = calculateTriangleDistortion(vertexD, vertexA, intersection);

	// Sort the triangle distortion amounts
	std::sort(std::begin(alphaValues), std::end(alphaValues), std::greater<double>());

	// Calculate and return the quadrilateral distortion
	return (alphaValues[2] * alphaValues[3]) / (alphaValues[0] * alphaValues[1]);
}

const double EvaluationFunctions::calculateDistortion2(const Quadrilateral &quadrilateral) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Calculate cross product for vertex A
	Vector AB(vertexA, vertexB);
	Vector AD(vertexA, vertexD);
	double cpA = GeometricFunctions::crossProduct(AB, AD);

	// Calculate cross product for vertex B
	Vector BC(vertexB, vertexC);
	Vector BA(vertexB, vertexA);
	double cpB = GeometricFunctions::crossProduct(BC, BA);

	// Calculate cross product for vertex C
	Vector CD(vertexC, vertexD);
	Vector CB(vertexC, vertexB);
	double cpC = GeometricFunctions::crossProduct(CD, CB);

	// Calculate cross product for vertex D
	Vector DA(vertexD, vertexA);
	Vector DC(vertexD, vertexC);
	double cpD = GeometricFunctions::crossProduct(DA, DC);

	// Calculate square length total values
	double squareSumA = pow(AB.getLength(), 2) + pow(AD.getLength(), 2);
	double squareSumB = pow(BC.getLength(), 2) + pow(BA.getLength(), 2);
	double squareSumC = pow(CD.getLength(), 2) + pow(CB.getLength(), 2);
	double squareSumD = pow(DA.getLength(), 2) + pow(DC.getLength(), 2);

	// Calculate the nominator and denominator
	double nominator = abs(cpA) + abs(cpB) + abs(cpC) + abs(cpD);
	double denominator = squareSumA + squareSumB + squareSumC + squareSumD;

	// Return the distortion value
	return 2 * sqrt(sqrt(nominator / denominator));
}

const double EvaluationFunctions::calculateMaximumWarpage(const Quadrilateral &quadrilateral) {

	// Calculate warpage amount on both diagonals
	double horizontalWarpage = calculateWarpage(quadrilateral, HORIZONTAL);
	double verticalWarpage = calculateWarpage(quadrilateral, VERTICAL);

	// Return the horizontal warpage amount if it is greater
	if (horizontalWarpage > verticalWarpage) {
		return horizontalWarpage;
	}

	// Return the vertical warpage amount elsewhere
	return verticalWarpage;
}

const double EvaluationFunctions::calculateAspectRatio(const Quadrilateral &quadrilateral) {

	// Project the quadrilateral onto a plane in case it is not planar
	const Quadrilateral projectedQuadrilateral = projectQuadrilateral(quadrilateral);

	// Get the vertices of the quadrilateral
	const Vertex vertexA = projectedQuadrilateral.getVertexA();
	const Vertex vertexB = projectedQuadrilateral.getVertexB();
	const Vertex vertexC = projectedQuadrilateral.getVertexC();
	const Vertex vertexD = projectedQuadrilateral.getVertexD();

	// Find the middle point of the edges
	const Vertex midAB = (vertexA + vertexB) / 2;
	const Vertex midBC = (vertexB + vertexC) / 2;
	const Vertex midCD = (vertexC + vertexD) / 2;
	const Vertex midDA = (vertexD + vertexA) / 2;

	// Create edges passing through the middle points
	const Edge verticalEdge(midAB, midCD);
	const Edge horizontalEdge(midBC, midDA);

	// Calculate the aspect-ratio by dividing the longer edge by shorter one
	double aspectRatio;
	if (verticalEdge.getLength() > horizontalEdge.getLength()) {
		aspectRatio = verticalEdge.getLength() / horizontalEdge.getLength();
	} else {
		aspectRatio = horizontalEdge.getLength() / verticalEdge.getLength();
	}

	// Return the aspect-ratio value
	return aspectRatio;
}

const double EvaluationFunctions::calculateJacobianDeterminant(const Edge &left, const Edge &right) {

	// Calculate the determinant value for x-y coordinates
	return left.getLengthX() * right.getLengthY() - right.getLengthX() * left.getLengthY();
}

const double EvaluationFunctions::calculateWarpage(const Quadrilateral &quadrilateral, AlignmentType alignment) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Calculate the warpage of the quadrilateral on given diagonal
	Angle warpage = 0.0;
	if (alignment == HORIZONTAL) {

		// Get the edges of the quadrilateral for the horizontal diagonal
		const Vector AB(vertexA, vertexB);
		const Vector AD(vertexA, vertexD);
		const Vector CB(vertexC, vertexB);
		const Vector CD(vertexC, vertexD);

		// Calculate the normals for both triangles for the horizontal diagonal
		const Normal normalABD = GeometricFunctions::findNormal(AB, AD);
		const Normal normalCDB = GeometricFunctions::findNormal(CD, CB);

		// Calculate the angle between the normals for the horizontal diagonal
		warpage = GeometricFunctions::calculateAngle(normalABD, normalCDB);

	} else {

		// Get the edges of the quadrilateral for the vertical diagonal
		const Vector BA(vertexB, vertexA);
		const Vector BC(vertexB, vertexC);
		const Vector DA(vertexD, vertexA);
		const Vector DC(vertexD, vertexC);

		// Calculate the normals for both triangles for the vertical diagonal
		const Normal normalBCA = GeometricFunctions::findNormal(BC, BA);
		const Normal normalDAC = GeometricFunctions::findNormal(DA, DC);

		// Calculate the angle between the normals for the vertical diagonal
		warpage = GeometricFunctions::calculateAngle(normalBCA, normalDAC);
	}

	// Return the warpage
	return warpage;
}

const double EvaluationFunctions::calculateTriangleDistortion(const Vertex &a, const Vertex &b, const Vertex &c) {

	// Get the edges of the triangle
	const Vector edgeAB(a, b);
	const Vector edgeCA(c, a);
	const Vector edgeCB(c, b);

	// Calculate the nominator and denominator
	const double areaElement = GeometricFunctions::crossProduct(edgeCA, edgeCB);
	const double squareSum = pow(edgeCA.getLength(), 2) + pow(edgeAB.getLength(), 2) + pow(edgeCB.getLength(), 2);

	// Find the normal direction
	int normalDirection;
	if (GeometricFunctions::crossProduct(edgeCA, edgeCB) > 0) {
		normalDirection = 1;
	} else {
		normalDirection = -1;
	}

	// Return the triangle distortion value
	return normalDirection * 2 * sqrt(3) * abs(areaElement) / squareSum;
}

const Vertex EvaluationFunctions::calculateCornerAverage(const Quadrilateral &quadrilateral) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Create and return the average vertex
	return (vertexA + vertexB + vertexC + vertexD) / 4;
}

const Normal EvaluationFunctions::calculateNormalAverage(const Quadrilateral &quadrilateral) {

	// Get the vertices of the quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Calculate the normals on the first vertex
	const Vector AB(vertexA, vertexB);
	const Vector AD(vertexA, vertexD);
	const Normal normalA = GeometricFunctions::findNormal(AB, AD);

	// Calculate the normals on the second vertex
	const Vector BC(vertexB, vertexC);
	const Vector BA(vertexB, vertexA);
	const Normal normalB = GeometricFunctions::findNormal(BC, BA);

	// Calculate the normals on the third vertex
	const Vector CD(vertexC, vertexD);
	const Vector CB(vertexC, vertexB);
	const Normal normalC = GeometricFunctions::findNormal(CD, CB);

	// Calculate the normals on the fourth vertex
	const Vector DA(vertexD, vertexA);
	const Vector DC(vertexD, vertexC);
	const Normal normalD = GeometricFunctions::findNormal(DA, DC);

	// Create start and end vertices for the normal
	const Vertex startVertex = (normalA.start + normalB.start + normalC.start + normalD.start) / 4;
	const Vertex endVertex = (normalA.end + normalB.end + normalC.end + normalD.end) / 4;

	// Create the average normal
	const Normal average(startVertex, endVertex);

	// Normalize the average normal into a unit vector
	const Normal normal = GeometricFunctions::normalizeVector(average);

	// Return the unit normal
	return normal;
}

const void EvaluationFunctions::projectTriangle(Edge &left, Edge &right) {

	// Create a temporary edge to complete the triangle
	const Vector leftover(left.end, right.end);

	// Get the edge lengths
	double leftEdgeLength = left.getLength();
	double rightEdgeLength = right.getLength();
	double leftoverLength = leftover.getLength();

	// Calculate the x-y values for the third vertex
	double x = (pow(leftEdgeLength, 2) - pow(leftoverLength, 2) + pow(rightEdgeLength, 2)) / (2 * rightEdgeLength);
	double y = sqrt(pow(leftEdgeLength, 2) - pow(x, 2));

	// Create vertices that are aligned with z=0 plane
	const Vertex middleVertex(0, 0);
	const Vertex rightVertex(rightEdgeLength, 0);
	const Vertex leftVertex(x, y);

	// Update the edge coordinates
	left.start = middleVertex;
	left.end = leftVertex;
	right.start = middleVertex;
	right.end = rightVertex;
}

const Quadrilateral EvaluationFunctions::projectQuadrilateral(const Quadrilateral &quadrilateral) {

	// Calculate the average of the corner points
	const Vertex origin = calculateCornerAverage(quadrilateral);

	// Calculate the average of the normals of the corner points
	const Normal normal = calculateNormalAverage(quadrilateral);

	// Get the vertices of the original quadrilateral
	const Vertex vertexA = quadrilateral.getVertexA();
	const Vertex vertexB = quadrilateral.getVertexB();
	const Vertex vertexC = quadrilateral.getVertexC();
	const Vertex vertexD = quadrilateral.getVertexD();

	// Create vectors from the origin to the each vertex of the quadrilateral
	const Vector vectorA(origin, vertexA);
	const Vector vectorB(origin, vertexB);
	const Vector vectorC(origin, vertexC);
	const Vector vectorD(origin, vertexD);

	// Calculate the distance to the plane by taking dot product of each vertex with the normal
	double distanceA = GeometricFunctions::dotProduct(normal, vectorA);
	double distanceB = GeometricFunctions::dotProduct(normal, vectorB);
	double distanceC = GeometricFunctions::dotProduct(normal, vectorC);
	double distanceD = GeometricFunctions::dotProduct(normal, vectorD);

	// Calculate the projection point for the first vertex
	double x = vertexA.x - (normal.start.x + distanceA * normal.getLengthX());
	double y = vertexA.y - (normal.start.y + distanceA * normal.getLengthY());
	double z = vertexA.z - (normal.start.z + distanceA * normal.getLengthZ());
	const Vertex projectedA(x, y, z);

	// Calculate the projection point for the second vertex
	x = vertexB.x - (normal.start.x + distanceB * normal.getLengthX());
	y = vertexB.y - (normal.start.y + distanceB * normal.getLengthY());
	z = vertexB.z - (normal.start.z + distanceB * normal.getLengthZ());
	const Vertex projectedB(x, y, z);

	// Calculate the projection point for the third vertex
	x = vertexC.x - (normal.start.x + distanceC * normal.getLengthX());
	y = vertexC.y - (normal.start.y + distanceC * normal.getLengthY());
	z = vertexC.z - (normal.start.z + distanceC * normal.getLengthZ());
	const Vertex projectedC(x, y, z);

	// Calculate the projection point for the fourth vertex
	x = vertexD.x - (normal.start.x + distanceD * normal.getLengthX());
	y = vertexD.y - (normal.start.y + distanceD * normal.getLengthY());
	z = vertexD.z - (normal.start.z + distanceD * normal.getLengthZ());
	const Vertex projectedD(x, y, z);

	// Create the quadrilateral with projected vertices
	const Quadrilateral projection(projectedA, projectedB, projectedC, projectedD);

	// Return the projected quadrilateral
	return projection;
}
