#pragma once

class TunnelSegment
{
private:
	float x, y, z; //position
	float size; //size of the segment ("radius" of the segment)
	unsigned int color; //color of the segment
public:
	TunnelSegment();
	~TunnelSegment();
	void placeSegment(float x, float y, float z, float size, unsigned int color);
	float getX();
	float getY();
	float getZ();
	float getSize();
	unsigned int getColor();
};
