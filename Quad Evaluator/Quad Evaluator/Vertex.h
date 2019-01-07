#ifndef VERTEX
#define VERTEX

struct Vertex {

	double x;
	double y;
	double z;

	Vertex(double x = 0.0f, double y = 0.0f, double z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vertex(const Vertex& vertex) {
		x = vertex.x;
		y = vertex.y;
		z = vertex.z;
	}

	Vertex operator+(const Vertex& vertex) const {
		return Vertex(x + vertex.x, y + vertex.y, z + vertex.z);
	}

	Vertex operator-(const Vertex& vertex) const {
		return Vertex(x - vertex.x, y - vertex.y, z - vertex.z);
	}

	Vertex operator*(const double value) const {
		return Vertex(value * x, value * y, value * z);
	}

	Vertex operator*(const Vertex& vertex) const {
		return Vertex(x * vertex.x, y * vertex.y, z * vertex.z);
	}

	Vertex operator/(const double value) const {
		double r = double(1.0) / value;
		return *this * r;
	}

	Vertex& operator+=(const Vertex& vertex) {
		x += vertex.x;
		y += vertex.y;
		z += vertex.z;
		return *this;
	}

	Vertex& operator-=(const Vertex& vertex) {
		x -= vertex.x;
		y -= vertex.y;
		z -= vertex.z;
		return *this;
	}

	Vertex& operator*=(const double value) {
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	Vertex& operator*=(const Vertex& vertex) {
		x *= vertex.x;
		y *= vertex.y;
		z *= vertex.z;
		return *this;
	}

	Vertex& operator/=(const double value) {
		double r = double(1.0) / value;
		*this *= r;
		return *this;
	}
};

#endif
