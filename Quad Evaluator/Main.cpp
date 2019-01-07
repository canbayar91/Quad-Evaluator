#include "EvaluationFunctions.h"
#include "AngleStatistics.h"
#include "MeshStatistics.h"
#include "MeshReader.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

int main(int argc, char *argv[]) {

	// Read the file name from command line
	std::string filename = argv[1];

	// Read the mesh from input file
	std::vector<Quadrilateral> quadrilateralList = MeshReader::getInstance()->readMesh(filename);

	// Calculate the angle statistics of the quadrilateral
	AngleStatistics angleStatistics(quadrilateralList);

	// Calculate the scaled jacobian matrix metric for the mesh
	MeshStatistics scaledJacobianStatistics(SCALED_JACOBIAN);
	for (unsigned int i = 0; i < quadrilateralList.size(); i++) {
		double scaledJacobian = EvaluationFunctions::calculateScaledJacobian(quadrilateralList[i]);
		scaledJacobianStatistics.updateStatistics(scaledJacobian);
		// std::cout << scaledJacobian << std::endl;
	}

	// Calculate the distortion metric for the mesh
	MeshStatistics distortionStatistics(DISTORTION);
	for (unsigned int i = 0; i < quadrilateralList.size(); i++) {
		double distortion = EvaluationFunctions::calculateDistortion2(quadrilateralList[i]);
		distortionStatistics.updateStatistics(distortion);
		// std::cout << distortion << std::endl;
	}

	// Calculate the warpage metric for the mesh
	MeshStatistics warpageStatistics(WARPAGE);
	for (unsigned int i = 0; i < quadrilateralList.size(); i++) {
		double warpage = EvaluationFunctions::calculateMaximumWarpage(quadrilateralList[i]);
		warpageStatistics.updateStatistics(warpage);
		// std::cout << warpage << std::endl;
	}

	// Calculate the aspect-ration metric for the mesh
	MeshStatistics aspectRatioStatistics(ASPECT_RATIO);
	for (unsigned int i = 0; i < quadrilateralList.size(); i++) {
		double aspectRatio = EvaluationFunctions::calculateAspectRatio(quadrilateralList[i]);
		aspectRatioStatistics.updateStatistics(aspectRatio);
		// std::cout << aspectRatio << std::endl;
	}

	// Delete the output file, if it is created previously
	const char* outputFile = "results.txt";
	std::remove(outputFile);

	// Output the minimum and maximum angle values
	angleStatistics.outputStatistics(outputFile);

	// Output the metric results
	scaledJacobianStatistics.outputStatistics(outputFile);
	distortionStatistics.outputStatistics(outputFile);
	warpageStatistics.outputStatistics(outputFile);
	aspectRatioStatistics.outputStatistics(outputFile);
	
	// Create the histograms of the metric calculations
	if (argc == 3 && strcmp(argv[2], "-h") == 0) {
		scaledJacobianStatistics.createHistogram("Histogram (Scaled Jacobian).csv");
		distortionStatistics.createHistogram("Histogram (Distortion).csv");
		warpageStatistics.createHistogram("Histogram (Warpage).csv");
		aspectRatioStatistics.createHistogram("Histogram (Aspect Ratio).csv");
	}

	// Finish the program by pressing a key
	std::cout << "Metric calculation completed. Press enter to continue..." << std::endl;
	getchar();
	return 0;
}