#ifndef MESH_READER
#define MESH_READER

#include "Mesh.h"
#include <string>

class MeshReader {
public:

	// Returns the singleton mesh reader instance
	static MeshReader* getInstance();

	// Reads the quadrilateral mesh in the given filepath
	void readQuadrilateralMesh(std::string filepath, Mesh* &mesh);

	// Reads the triangle mesh in the given filepath
	void readTriangleMesh(std::string filepath, Mesh* &mesh);

private:

	// Singleton mesh reader instance
	static MeshReader* instance;

	// Default constuctor
	MeshReader();

	// Destructor
	~MeshReader();

};

#endif
