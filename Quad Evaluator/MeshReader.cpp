#include "MeshReader.h"
#include "Quadrilateral.h"
#include "Triangle.h"
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

void MeshReader::readQuadrilateralMesh(std::string filepath, Mesh* &mesh) {

	// Open the file in given location
	std::ifstream infile(filepath);

	// Read the file format
	std::string format;
	infile >> format;

	// Read the mesh information
	unsigned int numVertices, numFaces, numEdges;
	infile >> numVertices >> numFaces >> numEdges;

	// Read the vertices from the file
	for (unsigned int i = 0; i < numVertices; i++) {

		// Read vertex coordinates
		double x, y, z;
		infile >> x >> y >> z;

		// Add a new vertex to the mesh
		mesh->addVertex(x, y, z);
	}

	// Read the faces from the file
	for (unsigned int i = 0; i < numFaces; i++) {

		// Read the number of vertices (always 4 for quadrilateral)
		unsigned int vertexCount;
		infile >> vertexCount;

		// Read the quadrilateral vertices
		unsigned int a, b, c, d;
		infile >> a >> b >> c >> d;

		// Create and add a new quadrilateral to the mesh
		mesh->addQuadrilateralFace(a, b, c, d);
	}

	// Close the input file
	infile.close();
}

void MeshReader::readTriangleMesh(std::string filepath, Mesh* &mesh) {

	// Open the file in given location
	std::ifstream infile(filepath);

	// Read the file format
	std::string format;
	infile >> format;

	// Read the mesh information
	unsigned int numVertices, numFaces, numEdges;
	infile >> numVertices >> numFaces >> numEdges;

	// Read the vertices from the file
	for (unsigned int i = 0; i < numVertices; i++) {

		// Read vertex coordinates
		double x, y, z;
		infile >> x >> y >> z;

		// Add a new vertex to the mesh
		mesh->addVertex(x, y, z);
	}

	// Read the faces from the file
	for (unsigned int i = 0; i < numFaces; i++) {

		// Read the number of vertices (always 3 for triangle)
		unsigned int vertexCount;
		infile >> vertexCount;

		// Read the triangle vertices
		unsigned int a, b, c;
		infile >> a >> b >> c;

		// Create and add a new triangle to the mesh
		mesh->addTriangleFace(a, b, c);
	}

	// Close the input file
	infile.close();
}
