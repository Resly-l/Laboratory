#pragma once
#include <vector>
#include "mathematics.h"

class Vertex
{
public:
	Vector worldPosition;
	Vector viewPosition;
	Vector normal;
	Vector texCoord;

public:
	const Vertex GetInterpolated(const Vertex& rhs, float alpha) const;

public:
	Vertex operator +(const Vertex& rhs) const;
	Vertex& operator +=(const Vertex& rhs);
	Vertex operator -(const Vertex& rhs) const;
	Vertex& operator -=(const Vertex& rhs);
	Vertex operator *(float factor) const;
	Vertex& operator *=(float factor);
	Vertex operator /(float factor) const;
	Vertex& operator /=(float factor);
};

struct Line
{
	Vertex from;
	Vertex to;
};

struct Triangle
{
	Vertex v0;
	Vertex v1;
	Vertex v2;
};

using VertexBuffer = std::vector<Vertex>;
using IndexBuffer = std::vector<unsigned int>;