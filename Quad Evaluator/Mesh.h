#ifndef MESH
#define MESH

#include "Primitive.h"
#include <vector>

enum MeshType {
	QUADRILATERAL_MESH,
	TRIANGLE_MESH
};

class Mesh {
public:

	Mesh(MeshType meshType = QUADRILATERAL_MESH);
	~Mesh();

	void addVertex(double x, double y, double z);
	void addQuadrilateralFace(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
	void addTriangleFace(unsigned int a, unsigned int b, unsigned int c);

	size_t getVertexCount() const;
	size_t getFaceCount() const;

	const Vertex &getVertex(size_t index) const;
	const Primitive &getFace(size_t index) const;

	const std::vector<Vertex*> &getVertexList() const;
	const std::vector<Primitive*> &getFaceList() const;

private:

	MeshType meshType;

	std::vector<Vertex*> vertexList;
	std::vector<Primitive*> faceList;

};

#endif
