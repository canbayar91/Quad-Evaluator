#include "AngleStatistics.h"
#include "GeometricFunctions.h"
#include <fstream>

AngleStatistics::AngleStatistics(const Mesh* mesh) {

	// Reset the minimum and maximum angle values
	minimumValue = 360;
	maximumValue = 0;

	// Get the list of quadrilateral faces on the mesh
	std::vector<Primitive*> quadrilateralList = mesh->getFaceList();

	// Iterate through each quadrilateral in the mesh
	for (size_t i = 0; i < mesh->getFaceCount(); i++) {

		// Get the current quadrilateral
		const Quadrilateral* quadrilateral = static_cast<Quadrilateral*>(quadrilateralList[i]);

		// Get vectors AB and AD
		const Vector AB(quadrilateral->a, quadrilateral->b);
		const Vector AD(quadrilateral->a, quadrilateral->d);

		// Calculate and store the angle between the vectors
		double currentAngle = GeometricFunctions::calculateAngle(AB, AD);
		values.push_back(currentAngle);

		// Initialize the minimum and maximum angles
		minimumValue = currentAngle;
		maximumValue = currentAngle;

		// Get vectors BC and BA
		const Vector BC(quadrilateral->b, quadrilateral->c);
		const Vector BA(quadrilateral->b, quadrilateral->a);

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
		const Vector CD(quadrilateral->c, quadrilateral->d);
		const Vector CB(quadrilateral->c, quadrilateral->b);

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
		const Vector DA(quadrilateral->d, quadrilateral->a);
		const Vector DC(quadrilateral->d, quadrilateral->c);

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
