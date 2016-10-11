#pragma once

#include "Tunnel.h"
#include "GameWindow.h"
#include "Ship.h"
#include <cstdio>
#include <cstdlib>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glm/glm.hpp>
using namespace glm;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

class Renderer
{
private:
	//void drawSegment(TunnelSegment* segment); //draws a segment of a tunnel
	HDC hdc;
public:
	Renderer();
	~Renderer();
	bool bindToWindow(GameWindow* window);//binds opengl to the window
	void clearScreen();	//clears the screen
	void positionCamera(Ship* ship);
	void draw(Tunnel* tunnel); //draws an entire tunnel
	void draw(Ship* ship); //draws a ship
	//void drawModel(std::string file);
	void updateScreen(); //swaps the draw buffers
};

/*struct Triangle {
       
       int v1;
       int v2;
       int v3;
	   int v4;
       
};

struct Vertex {
      
      float x;
      float y;
      float z;
            
};*/