#include "Tunnel.h"

Tunnel::Tunnel(void)
{
}

Tunnel::~Tunnel(void)
{
	while(segments.size() > 0)
		segments.pop_back();
	segments.~deque<TunnelSegment>();
}

void Tunnel::generateSegment()
{
	//create a new segment
	TunnelSegment temp;
	//is there is more than 0 segments
	if(segments.size() > 0)
	{
		//generate random poisitions/colors
		//place the segment
		temp.placeSegment(((rand()%1300)*xVariance), 
			segments[segments.size()-1].getY()+distance,
			((rand()%1300)*yVariance),
			rand()%(maxSize - minSize)+minSize,
			rand()*(colorMask/RAND_MAX));
		joinSegments(segments[segments.size() - 1], temp);
	}
	//if this if the first segment
	else
	{
		temp.placeSegment(0, 0, 0, 10, rand());
	}
	//put the new segment into the array
	segments.push_back(temp);
	//if there are more segments than we need
	if(segments.size() > Tunnel::segmentsOnScreen)
	{
		//delete the first segment
		segments.pop_front();
	}
}

int Tunnel::getSegmentCount()
{
	return this->segments.size();
}

TunnelSegment* Tunnel::getSegment(int index)
{
	if(index > segments.size())
		return NULL;
	return &segments[index];
}

void Tunnel::generateSegments()
{
	//create segmentsOnScreen amount of segments
	while(segments.size() < Tunnel::segmentsOnScreen)
	{
		generateSegment();
	}
}

void Tunnel::joinSegments(TunnelSegment& first, TunnelSegment& second)
{
	//generate vertices
}
