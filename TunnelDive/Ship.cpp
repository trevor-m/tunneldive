#include "Ship.h"

Ship::Ship(void)
{
	this->x = 0.0f;
	this->y = 4.0f;
	this->z = 0.0f;
	this->downSpeed = 1.5f;
	this->turnSpeed = 0.75f;
	this->xAngle = 0.0f;
	this->yAngle = 0.0f;
	this->zAngle = 0.0f;
	this->actualXAngle = 0.0f;
	this->actualYAngle = 0.0f;
	this->actualZAngle = 0.0f;
}

Ship::~Ship(void)
{
}

void Ship::getInput()
{
	//checkMouse();
	bool down = true;
	//get input and move ship
	if(GetAsyncKeyState(VkKeyScan('s')))
	{
		x -= this->turnSpeed;
		this->zAngle = 5.0f;
		down = false;
	}
	else if(GetAsyncKeyState(VkKeyScan('w')))
	{
		x += this->turnSpeed;
		this->zAngle = -2.5f;
		down = true;
	}
	else
	{
		this->zAngle = 0.0f;
	}

	if(GetAsyncKeyState(VkKeyScan('d')))
	{
		z -= this->turnSpeed;
		if(down)
		{
			//this->xAngle = 15.0f;
			this->yAngle = 15.0f;
		}
		else
		{
			//this->xAngle = 15.0f;
			this->yAngle = -15.0f;
		}
	}
	else if(GetAsyncKeyState(VkKeyScan('a')))
	{
		z += this->turnSpeed;
		if(down)
		{
			//this->xAngle = -15.0f;
			this->yAngle = -15.0f;
		}
		else
		{
			//this->xAngle = -15.0f;
			this->yAngle = 15.0f;
		}
	}
	else
	{
		this->xAngle = 0.0f;
		this->yAngle = 0.0f;
	}

	//boost
	if(GetAsyncKeyState(VK_SHIFT))
	{
		this->downSpeed = 9.0f;
	}
	//brake
	else if (!GetAsyncKeyState(VK_SPACE))
	{
		this->downSpeed = 1.0f;
	}
	else
	{
		this->downSpeed = 1.5f;
	}


	//rotate smoothly
	if(this->actualXAngle < this->xAngle)
	{
		this->actualXAngle += 1.5f;
	}
	if(this->actualXAngle > this->xAngle)
	{
		this->actualXAngle -= 1.5f;
	}

	if(this->actualYAngle < this->yAngle)
	{
		this->actualYAngle += 2.5f;
	}
	if(this->actualYAngle > this->yAngle)
	{
		this->actualYAngle -= 2.5f;
	}

	if(this->actualZAngle < this->zAngle)
	{
		this->actualZAngle += 0.5f;
	}
	if(this->actualZAngle > this->zAngle)
	{
		this->actualZAngle -= 0.5f;
	}
}

void Ship::moveForward()
{
	this->y += this->downSpeed;
}

bool Ship::checkCollisions(Tunnel* tunnel)
{
	//generate further segments
	if(this->y > tunnel->getSegment(0)->getY() + 40)
	{
		tunnel->generateSegment();
	}

	//for (int i = 0; i < tunnel->getSegmentCount(); i++) {
		//if(tunnel->getSegment(i)->getY() < y+depth && tunnel->getSegment(i)->getY() > y-depth)
	//}
	return false;
}

void Ship::changeSpeed(float newSpeed)
{
	this->downSpeed = newSpeed;
}

float Ship::getX()
{
	return this->x;
}

float Ship::getY()
{
	return this->y;
}

float Ship::getXAngle()
{
	return this->actualXAngle;;
}

float Ship::getYAngle()
{
	return this->actualYAngle;
}
float Ship::getZAngle()
{
	return this->actualZAngle;
}

float Ship::getZ()
{
	return this->z;
}