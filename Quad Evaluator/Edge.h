#ifndef EDGE
#define EDGE

#include "Vertex.h"

class Edge {
public:

	Edge(const Vertex &start, const Vertex &end);

	void setStart(const Vertex &start);
	void setEnd(const Vertex &end);

	const Vertex &getStart() const;
	const Vertex &getEnd() const;

	const double getLength() const;

	const double getProductX() const;
	const double getProductY() const;
	const double getProductZ() const;

	const double getLengthX() const;
	const double getLengthY() const;
	const double getLengthZ() const;
	
private:

	Vertex start;
	Vertex end;

};

#endif
