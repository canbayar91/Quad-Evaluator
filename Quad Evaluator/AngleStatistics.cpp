#include "AngleStatistics.h"
#include "GeometricFunctions.h"
#include <fstream>

AngleStatistics::AngleStatistics(const std::vector<Quadrilateral> &mesh) {

	// Reset the minimum and maximum angle values
	minimumValue = 360;
	maximumValue = 0;

	// Iterate through each quadrilateral in the mesh
	for (unsigned int i = 0; i < mesh.size(); i++) {

		// Get the current quadrilateral
		const Quadrilateral &quadrilateral = mesh[i];

		// Get the vertices of the quadrilateral
		const Vertex vertexA = quadrilateral.getVertexA();
		const Vertex vertexB = quadrilateral.getVertexB();
		const Vertex vertexC = quadrilateral.getVertexC();
		const Vertex vertexD = quadrilateral.getVertexD();

		// Get vectors AB and AD
		const Vector AB(vertexA, vertexB);
		const Vector AD(vertexA, vertexD);

		// Calculate and store the angle between the vectors
		double currentAngle = GeometricFunctions::calculateAngle(AB, AD);
		values.push_back(currentAngle);

		// Initialize the minimum and maximum angles
		minimumValue = currentAngle;
		maximumValue = currentAngle;

		// Get vectors BC and BA
		const Vector BC(vertexB, vertexC);
		const Vector BA(vertexB, vertexA);

		// Calculate and store the angle between the vectors
		currentAngle = GeometricFunctions::calculateAngle(BC, BA);
		values.push_back(currentAngle);

		// Update the minimum angle
		if (currentAngle < minimumValue) {
			minimumValue = currentAngle;
		}

		// Update the maximum angle
		if (currentAngle > maximumValue) {
			maximumValue = currentAngle;
		}

		// Get vectors CD and CB
		const Vector CD(vertexC, vertexD);
		const Vector CB(vertexC, vertexB);

		// Calculate and store the angle between the vectors
		currentAngle = GeometricFunctions::calculateAngle(CD, CB);
		values.push_back(currentAngle);

		// Update the minimum angle
		if (currentAngle < minimumValue) {
			minimumValue = currentAngle;
		}

		// Update the maximum angle
		if (currentAngle > maximumValue) {
			maximumValue = currentAngle;
		}

		// Get vectors DA and DC
		const Vector DA(vertexD, vertexA);
		const Vector DC(vertexD, vertexC);

		// Calculate and store the angle between the vectors
		currentAngle = GeometricFunctions::calculateAngle(DA, DC);
		values.push_back(currentAngle);

		// Update the minimum angle
		if (currentAngle < minimumValue) {
			minimumValue = currentAngle;
		}

		// Update the maximum angle
		if (currentAngle > maximumValue) {
			maximumValue = currentAngle;
		}
	}
}

void AngleStatistics::outputStatistics(const std::string filename) {

	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// Output the statistics
	file << "Minimum mesh angle: " << minimumValue << std::endl;
	file << "Maximum mesh angle: " << maximumValue << std::endl << std::endl;

	// Close the file
	file.close();
}

void AngleStatistics::createHistogram(const std::string filename) {
	
	// Delete the file, if it is previously created
	std::remove(filename.c_str());

	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// Iterate through the list and output the values
	for (size_t i = 0; i < values.size(); i++) {
		file << values[i] << std::endl;
	}

	// Close the file
	file.close();
}
