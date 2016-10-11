#pragma once

#include "Tunnel.h"
#include <windows.h>

class Ship
{
private:
	float x, y, z;
	float downSpeed;
	float turnSpeed;
	float xAngle;
	float yAngle; //left and right turning
	float zAngle; //up and down turning
	float actualXAngle;
	float actualYAngle;
	float actualZAngle;
	void checkMouse();
public:
	Ship(void);
	~Ship(void);
	void getInput(); //updates the ships position based on input
	void moveForward(); //move the ship forward
	bool checkCollisions(Tunnel* tunnel); //checks for collisions with the tunnel
	float getX();
	float getY();
	float getZ();
	float getXAngle();
	float getYAngle();
	float getZAngle();
	void changeSpeed(float newSpeed);
};
