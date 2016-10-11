#pragma once

#include "TunnelSegment.h"
#include <deque>
#include <glm/glm.hpp>
using namespace glm;

class Tunnel
{
private:
	static const int segmentsOnScreen = 25; //How many segments are on screen at a time
	float xVariance = 0.02f;
	float yVariance = 0.02f;
	float distance = 20.0f;
	int minSize = 8;
	int maxSize = 30;
	unsigned int colorMask = 0xFFFF00; //0xFFFFFF for blue/green color scheme
	//unsigned int colorLow = 0x000101;
	//unsigned int colorHigh = 0x00FFFF;

	std::deque<TunnelSegment> segments; //Array of segments in this map
	std::deque<float*> vertices;
	std::deque<float*> normals;

	void joinSegments(TunnelSegment& first, TunnelSegment& second);
	//unsigned int fogColor; //color of the fog
public:
	Tunnel();
	~Tunnel();

	void generateSegment(); //Randomly generates the next segment of the map, and pops the old one off the front
	void generateSegments();
	int getSegmentCount();
	TunnelSegment* getSegment(int index);
};
