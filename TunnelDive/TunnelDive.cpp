#include "TunnelDive.h"

TunnelDive::TunnelDive()
{
	this->window = new GameWindow();
	this->renderer = new Renderer();
	this->tunnel = new Tunnel();
	this->ship = new Ship();
	srand(GetTickCount());
}

TunnelDive::~TunnelDive()
{
	delete this->window;
	delete this->renderer;
	delete this->tunnel;
	delete this->ship;
}

void TunnelDive::Main(HINSTANCE hInstance, WNDPROC WndProc)
{
	//create a window
	window->createWindow("TunnelDive", "TDEngine", hInstance, WndProc);
	//bind the renderer to the window
	renderer->bindToWindow(this->window);
	//create some segments
	tunnel->generateSegments();
	//game loop
    while(this->window->messagePump())
	{
		//update logic
		ship->moveForward();
		ship->getInput();
		ship->checkCollisions(tunnel);

		//begin drawing
		renderer->clearScreen();
		//move camera
		renderer->positionCamera(ship);
		//draw tunnel
		renderer->draw(tunnel);
		//draw ship
		renderer->draw(ship);
		//renderer->drawModel("tower.obj");
		//end drawing
		renderer->updateScreen();

		//wait
		//Sleep(25);
	}
}
