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
	Mesh* quadrilateralMesh = new Mesh(QUADRILATERAL_MESH);
	MeshReader::getInstance()->readQuadrilateralMesh(filename, quadrilateralMesh);
	std::cout << "Mesh is read. Starting metric analysis..." << std::endl;

	// Calculate the angle statistics of the quadrilateral
	AngleStatistics angleStatistics(quadrilateralMesh);

	// Get the list of quadrilateral faces on the mesh
	std::vector<Primitive*> quadrilateralList = quadrilateralMesh->getFaceList();

	// Calculate the scaled jacobian matrix metric for the mesh
	MeshStatistics scaledJacobianStatistics(SCALED_JACOBIAN);
	for (size_t i = 0; i < quadrilateralMesh->getFaceCount(); i++) {
		const Quadrilateral* quadrilateral = static_cast<Quadrilateral*>(quadrilateralList[i]);
		double scaledJacobian = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral);
		scaledJacobianStatistics.updateStatistics(scaledJacobian);
		// std::cout << scaledJacobian << std::endl;
	}

	// Calculate the distortion metric for the mesh
	MeshStatistics distortionStatistics(DISTORTION);
	for (size_t i = 0; i < quadrilateralMesh->getFaceCount(); i++) {
		const Quadrilateral* quadrilateral = static_cast<Quadrilateral*>(quadrilateralList[i]);
		double distortion = EvaluationFunctions::calculateDistortion2(quadrilateral);
		distortionStatistics.updateStatistics(distortion);
		// std::cout << distortion << std::endl;
	}

	// Calculate the warpage metric for the mesh
	MeshStatistics warpageStatistics(WARPAGE);
	for (size_t i = 0; i < quadrilateralMesh->getFaceCount(); i++) {
		const Quadrilateral* quadrilateral = static_cast<Quadrilateral*>(quadrilateralList[i]);
		double warpage = EvaluationFunctions::calculateMaximumWarpage(quadrilateral);
		warpageStatistics.updateStatistics(warpage);
		// std::cout << warpage << std::endl;
	}

	// Calculate the aspect-ration metric for the mesh
	MeshStatistics aspectRatioStatistics(ASPECT_RATIO);
	for (size_t i = 0; i < quadrilateralMesh->getFaceCount(); i++) {
		const Quadrilateral* quadrilateral = static_cast<Quadrilateral*>(quadrilateralList[i]);
		double aspectRatio = EvaluationFunctions::calculateAspectRatio(quadrilateral);
		aspectRatioStatistics.updateStatistics(aspectRatio);
		// std::cout << aspectRatio << std::endl;
	}

	// Delete the output file, if it is created previously
	const char* outputFile = "statistics.txt";
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
		scaledJacobianStatistics.createHistogram("Statistics(Scaled Jacobian).csv");
		distortionStatistics.createHistogram("Statistics(Distortion).csv");
		warpageStatistics.createHistogram("Statistics(Warpage).csv");
		aspectRatioStatistics.createHistogram("Statistics(Aspect-Ratio).csv");
		std::cout << "Individual element metrics generated and can be analyzed using Excel." << std::endl;
	}

	// Finish the program by pressing a key
	std::cout << "Metric calculation completed. Press enter to continue..." << std::endl;
	getchar();
	return 0;
}