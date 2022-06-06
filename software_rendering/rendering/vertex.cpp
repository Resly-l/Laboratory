#include "vertex.h"

const Vertex Vertex::GetInterpolated(const Vertex& rhs, float alpha) const
{
	Vertex interpolated;

	interpolated.worldPosition = worldPosition + (rhs.worldPosition - worldPosition) * alpha;
	interpolated.viewPosition = viewPosition + (rhs.viewPosition - viewPosition) * alpha;
	interpolated.normal = (normal + (rhs.normal - normal) * alpha).GetNormalized3();
	interpolated.texCoord = texCoord + (rhs.texCoord - texCoord) * alpha;

	return interpolated;
}

Vertex Vertex::operator+(const Vertex& rhs) const
{
	Vertex result;

	result.worldPosition = worldPosition + rhs.worldPosition;
	result.viewPosition = viewPosition + rhs.viewPosition;
	result.normal = normal + rhs.normal;
	result.texCoord = texCoord + rhs.texCoord;

	return result;
}

Vertex& Vertex::operator+=(const Vertex& rhs)
{
	return *this = *this + rhs;
}

Vertex Vertex::operator-(const Vertex& rhs) const
{
	Vertex result;

	result.worldPosition = worldPosition - rhs.worldPosition;
	result.viewPosition = viewPosition - rhs.viewPosition;
	result.normal = normal - rhs.normal;
	result.texCoord = texCoord - rhs.texCoord;

	return result;
}

Vertex& Vertex::operator-=(const Vertex& rhs)
{
	return *this = *this - rhs;
}

Vertex Vertex::operator*(float factor) const
{
	Vertex result;

	result.worldPosition = worldPosition * factor;
	result.viewPosition = viewPosition * factor;
	result.normal = normal * factor;
	result.texCoord = texCoord * factor;

	return result;
}

Vertex& Vertex::operator*=(float factor)
{
	return *this = *this * factor;
}

Vertex Vertex::operator/(float factor) const
{
	return *this * (1.0f / factor);
}

Vertex& Vertex::operator/=(float factor)
{
	return *this = *this / factor;
}