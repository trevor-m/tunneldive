#include "TunnelSegment.h"

TunnelSegment::TunnelSegment(void)
{
}

TunnelSegment::~TunnelSegment(void)
{
}

void TunnelSegment::placeSegment(float x, float y, float z, float size, unsigned int color)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->size = size;
	this->color = color;
}

float TunnelSegment::getX()
{
	return this->x;
}

float TunnelSegment::getY()
{
	return this->y;
}

float TunnelSegment::getZ()
{
	return this->z;
}

float TunnelSegment::getSize()
{
	return this->size;
}

unsigned int TunnelSegment::getColor()
{
	return this->color;
}