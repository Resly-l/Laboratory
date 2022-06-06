#pragma once
#include "vertex.h"

class VertexShader
{
public:
	virtual Vertex Shade(const Vertex& vertex) = 0;
};

class PixelShader
{
public:
	virtual Vector Shade(const Vertex& ps_in) = 0;
};