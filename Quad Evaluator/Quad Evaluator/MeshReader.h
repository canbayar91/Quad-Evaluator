#ifndef MESH_READER
#define MESH_READER

#include "Quadrilateral.h"
#include <string>
#include <vector>

class MeshReader {
public:

	// Returns the singleton mesh reader instance
	static MeshReader* getInstance();

	// Reads the mesh in the given filepath
	std::vector<Quadrilateral> readMesh(std::string filepath);

private:

	// Singleton mesh reader instance
	static MeshReader* instance;

	// Default constuctor
	MeshReader();

	// Destructor
	~MeshReader();

};

#endif