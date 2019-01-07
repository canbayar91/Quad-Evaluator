#include "MeshReader.h"
#include <fstream>

MeshReader* MeshReader::instance;

MeshReader::MeshReader() {
	instance = new MeshReader();
}

MeshReader::~MeshReader() {
	delete instance;
	instance = 0;
}

MeshReader* MeshReader::getInstance() {
	return instance;
}

std::vector<Quadrilateral> MeshReader::readMesh(std::string filepath) {

	// Open the file in given location
	std::ifstream infile(filepath);

	// Read the file format
	std::string format;
	infile >> format;

	// Read the mesh information
	unsigned int numVertices, numFaces, numEdges;
	infile >> numVertices >> numFaces >> numEdges;

	// Read the vertices from the file
	std::vector<Vertex> vertexList(numVertices);
	for (unsigned int i = 0; i < numVertices; i++) {

		// Read vertex coordinates
		double x, y, z;
		infile >> x >> y >> z;

		// Add it to the vertex list
		vertexList[i] = Vertex(x, y, z);
	}

	// Read the faces from the file
	std::vector<Quadrilateral> quadrilateralList(numFaces);
	for (unsigned int i = 0; i < numFaces; i++) {

		// Read the number of vertices (always 4 for quadrilateral)
		unsigned int vertexCount;
		infile >> vertexCount;

		// Read the quadrilateral vertices
		unsigned int a, b, c, d;
		infile >> a >> b >> c >> d;

		// Construct the quadrilateral and add it to the list
		Quadrilateral quadrilateral(vertexList[a], vertexList[b], vertexList[c], vertexList[d]);
		quadrilateralList[i] = quadrilateral;
	}

	// Close the input file
	infile.close();

	// Return the resulting list
	return quadrilateralList;
}