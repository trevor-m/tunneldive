#pragma once

#include "GameWindow.h"
#include "Renderer.h"
#include "Ship.h"

class TunnelDive
{
private:
	GameWindow* window;
	Renderer* renderer;
	Tunnel* tunnel;
	Ship* ship;
public:
	TunnelDive();
	~TunnelDive();
	void Main(HINSTANCE hInstance, WNDPROC WndProc);
};
