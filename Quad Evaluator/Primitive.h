#ifndef PRIMITIVE
#define PRIMITIVE

#include "Vector.h"
#include <string>

class Primitive {
public:

	virtual void textOutput(std::string filename) const = 0;
	virtual void offOutput(std::string filename) const = 0;

};

#endif
