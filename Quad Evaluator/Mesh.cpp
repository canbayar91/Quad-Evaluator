#include "Mesh.h"
#include "Quadrilateral.h"
#include "Triangle.h"

Mesh::Mesh(MeshType meshType) {
	this->meshType = meshType;
}

Mesh::~Mesh() {

	for (size_t i = 0; i < faceList.size(); i++) {
		delete faceList[i];
		faceList[i] = 0;
	}

	for (size_t i = 0; i < vertexList.size(); i++) {
		delete vertexList[i];
		vertexList[i] = 0;
	}
}

void Mesh::addVertex(double x, double y, double z) {
	Vertex* vertex = new Vertex(x, y, z);
	vertexList.push_back(vertex);
}

void Mesh::addQuadrilateralFace(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
	// TODO - Update quadrilateral interface to vertex pointers
	Quadrilateral* quadrilateral = new Quadrilateral(*vertexList[a], *vertexList[b], *vertexList[c], *vertexList[d]);
	faceList.push_back(quadrilateral);
}

void Mesh::addTriangleFace(unsigned int a, unsigned int b, unsigned int c) {
	// TODO - Update triangle interface to vertex pointers
	Triangle* triangle = new Triangle(*vertexList[a], *vertexList[b], *vertexList[c]);
	faceList.push_back(triangle);
}

size_t Mesh::getVertexCount() const {
	return vertexList.size();
}

size_t Mesh::getFaceCount() const {
	return faceList.size();
}

const Vertex &Mesh::getVertex(size_t index) const {
	return *vertexList[index];
}

const Primitive &Mesh::getFace(size_t index) const {
	return *faceList[index];
}

const std::vector<Vertex*> &Mesh::getVertexList() const {
	return vertexList;
}

const std::vector<Primitive*> &Mesh::getFaceList() const {
	return faceList;
}
