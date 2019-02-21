#include "QuadrilateralStatistics.h"
#include "GeometricFunctions.h"
#include <fstream>

QuadrilateralStatistics::QuadrilateralStatistics(const Mesh* mesh) {
	// TODO - Find the count of good and bad quads
}

void QuadrilateralStatistics::outputStatistics(const std::string filename) {

	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// TODO - Output statistics

	// Close the file
	file.close();
}

void QuadrilateralStatistics::createHistogram(const std::string filename) {

	// Delete the file, if it is previously created
	std::remove(filename.c_str());

	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// TODO - Output histogram

	// Close the file
	file.close();
}
