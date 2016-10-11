#include "Renderer.h"

Renderer::Renderer(void)
{

}

Renderer::~Renderer(void)
{
}

bool Renderer::bindToWindow(GameWindow* window)
{
	this->hdc = window->getHdc();
    PIXELFORMATDESCRIPTOR pfd = { 0 };

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;

    pfd.iPixelType = PFD_TYPE_RGBA ;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;

    int chosenPixelFormat = ChoosePixelFormat(this->hdc, &pfd);
    if(chosenPixelFormat == 0)
    {
        return false;
    }
    int result = SetPixelFormat(this->hdc, chosenPixelFormat, &pfd);
    if(result == NULL)
    {
        return false;
    }
    HGLRC hglrc = wglCreateContext(this->hdc);
    wglMakeCurrent(this->hdc, hglrc);

	//Initialize openGL
	glViewport(0, 0, window->getWidth(), window->getHeight());
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,(float)window->getWidth()/(float)window->getHeight(), 0, 300);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	glEnable(GL_CULL_FACE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL);

	//lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//fog
	float fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f};	
	glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.10f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
	glFogf(GL_FOG_START, 300.0f);				// Fog Start Depth
	glFogf(GL_FOG_END, 325.0f);				// Fog End Depth
	glEnable(GL_FOG);					// Enables GL_FOG
	glShadeModel(GL_SMOOTH);
	glEnable (GL_POLYGON_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	


	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	return true;
}

void Renderer::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glTranslatef(0.0f, 0.0f, 0.0f);
}

void Renderer::positionCamera(Ship* ship)
{
	gluLookAt(ship->getX()+0.3f, ship->getY()-1.6f, ship->getZ(),
			  ship->getX()-0.0f, ship->getY()+0.0f, ship->getZ(),
			  0.0f, 1.0f, 0.0f);
}

void Renderer::draw(Tunnel* tunnel)
{
	//drawing tunnel segments
	//the are connected to the one in front of them
	for(int i = tunnel->getSegmentCount()-2; i > 0; i--)
	{
		//left
		glBegin(GL_POLYGON);
			//set the color to the first segment
			glColor3ub(GetRValue(tunnel->getSegment(i)->getColor()),
					   GetGValue(tunnel->getSegment(i)->getColor()),
					   GetBValue(tunnel->getSegment(i)->getColor()));

			glVertex3f(tunnel->getSegment(i)->getX()-tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()-tunnel->getSegment(i)->getSize());

			glVertex3f(tunnel->getSegment(i)->getX()+tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()-tunnel->getSegment(i)->getSize());

			//set the color to the second segment
			glColor3ub(GetRValue(tunnel->getSegment(i+1)->getColor()),
					   GetGValue(tunnel->getSegment(i+1)->getColor()),
					   GetBValue(tunnel->getSegment(i+1)->getColor()));

			glVertex3f(tunnel->getSegment(i+1)->getX()+tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()-tunnel->getSegment(i+1)->getSize());

			glVertex3f(tunnel->getSegment(i+1)->getX()-tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()-tunnel->getSegment(i+1)->getSize());
		glEnd();
		//right
		glBegin(GL_POLYGON);
			//set the color to the first segment
			glColor3ub(GetRValue(tunnel->getSegment(i)->getColor()),
					   GetGValue(tunnel->getSegment(i)->getColor()),
					   GetBValue(tunnel->getSegment(i)->getColor()));

			glVertex3f(tunnel->getSegment(i)->getX()+tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()+tunnel->getSegment(i)->getSize());

			glVertex3f(tunnel->getSegment(i)->getX()-tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()+tunnel->getSegment(i)->getSize());

			//set the color to the second segment
			glColor3ub(GetRValue(tunnel->getSegment(i+1)->getColor()),
					   GetGValue(tunnel->getSegment(i+1)->getColor()),
					   GetBValue(tunnel->getSegment(i+1)->getColor()));

			glVertex3f(tunnel->getSegment(i+1)->getX()-tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()+tunnel->getSegment(i+1)->getSize());

			glVertex3f(tunnel->getSegment(i+1)->getX()+tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()+tunnel->getSegment(i+1)->getSize());
		glEnd();
		//top
		glBegin(GL_POLYGON);
			glVertex3f(tunnel->getSegment(i+1)->getX()-tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()-tunnel->getSegment(i+1)->getSize());

			glVertex3f(tunnel->getSegment(i+1)->getX()-tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()+tunnel->getSegment(i+1)->getSize());

			//set the color to the first segment
			glColor3ub(GetRValue(tunnel->getSegment(i)->getColor()),
					   GetGValue(tunnel->getSegment(i)->getColor()),
					   GetBValue(tunnel->getSegment(i)->getColor()));

			glVertex3f(tunnel->getSegment(i)->getX()-tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()+tunnel->getSegment(i)->getSize());

			glVertex3f(tunnel->getSegment(i)->getX()-tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()-tunnel->getSegment(i)->getSize());
		glEnd();
		//bottom
		glBegin(GL_POLYGON);
			//set the color to the second segment
			glColor3ub(GetRValue(tunnel->getSegment(i+1)->getColor()),
					   GetGValue(tunnel->getSegment(i+1)->getColor()),
					   GetBValue(tunnel->getSegment(i+1)->getColor()));

			glVertex3f(tunnel->getSegment(i+1)->getX()+tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()+tunnel->getSegment(i+1)->getSize());

			glVertex3f(tunnel->getSegment(i+1)->getX()+tunnel->getSegment(i+1)->getSize(),
					   tunnel->getSegment(i+1)->getY(),
					   tunnel->getSegment(i+1)->getZ()-tunnel->getSegment(i+1)->getSize());

			

			//set the color to the first segment
			glColor3ub(GetRValue(tunnel->getSegment(i)->getColor()),
					   GetGValue(tunnel->getSegment(i)->getColor()),
					   GetBValue(tunnel->getSegment(i)->getColor()));

			glVertex3f(tunnel->getSegment(i)->getX()+tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()-tunnel->getSegment(i)->getSize());

			glVertex3f(tunnel->getSegment(i)->getX()+tunnel->getSegment(i)->getSize(),
					   tunnel->getSegment(i)->getY(),
					   tunnel->getSegment(i)->getZ()+tunnel->getSegment(i)->getSize());

		glEnd();
	}
}

void Renderer::draw(Ship *ship)
{
	glPushMatrix();
	//glLoadIdentity();

	glTranslatef(ship->getX(), ship->getY(), ship->getZ());
	glRotatef(ship->getXAngle(), 1.0f, 0.0f, 0.0f);
	glRotatef(ship->getYAngle(), 0.0f, 1.0f, 0.0f);
	glRotatef(ship->getZAngle(), 0.0f, 0.0f, 1.0f);
	glTranslatef(-ship->getX(), -ship->getY(), -ship->getZ());


	glColor3f(0.2f, 0.2f, 0.2f);
	//Back (side facing you)
	glBegin(GL_POLYGON);
		glVertex3f(ship->getX()-0.1f, ship->getY()-1.0f, ship->getZ());
		glVertex3f(ship->getX(),	  ship->getY()-1.0f, ship->getZ()-0.3f);
		glVertex3f(ship->getX()+0.1f, ship->getY()-1.0f, ship->getZ());
		glVertex3f(ship->getX(),	  ship->getY()-1.0f, ship->getZ()+0.3f);
	glEnd();

	glColor3f(0.1f, 0.1f, 0.2f);
	//Left/Top side
	glBegin(GL_POLYGON);
	glVertex3f(ship->getX(), ship->getY(), ship->getZ());
	glVertex3f(ship->getX() , ship->getY() - 1.0f, ship->getZ() + 0.3f);
	glVertex3f(ship->getX() + 0.1f, ship->getY() - 1.0f, ship->getZ() );
	glEnd();

	//Right/Topside
	glBegin(GL_POLYGON);
	glVertex3f(ship->getX(), ship->getY(), ship->getZ());
	glVertex3f(ship->getX() + 0.1f, ship->getY() - 1.0f, ship->getZ());
	glVertex3f(ship->getX() , ship->getY() - 1.0f, ship->getZ() - 0.3f);	
	glEnd();

	//Left/Bottom side
	glBegin(GL_POLYGON);
	
	glVertex3f(ship->getX(), ship->getY() - 1.0f, ship->getZ() - 0.3f);
	glVertex3f(ship->getX() - 0.1f, ship->getY() - 1.0f, ship->getZ());
	glVertex3f(ship->getX(), ship->getY(), ship->getZ());
	
	glEnd();

	//Right/Bottom side
	glBegin(GL_POLYGON);
	
	glVertex3f(ship->getX() - 0.1f, ship->getY() - 1.0f, ship->getZ());
	glVertex3f(ship->getX(), ship->getY() - 1.0f, ship->getZ() + 0.3f);

	glVertex3f(ship->getX(), ship->getY(), ship->getZ());
	
	glEnd();
	
	glPopMatrix();
}

/*void Renderer::drawModel(std::string file)
{
	glTranslatef(0, 200, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	
	Vertex* v = new Vertex[5000];
	Triangle* t = new Triangle[5000];

	int vertexCount = 0;
	int triangleCount = 0;

	char line[100];

	FILE *fp = fopen(file.c_str(), "r");

	if(fp != NULL)
	{
		while(fgets(line, 99, fp))
		{
			  if(line[0] == 'v')
			  {
				  sscanf(line, "%*c %f %f %f", &v[vertexCount].x, &v[vertexCount].y, &v[vertexCount].z);                  
				  vertexCount++;
			  } 
			  else if(line[0] == 'f')
			  {
				  sscanf(line, "%*c %d%*s %d%*s %d%*s %d%*s", &t[triangleCount].v1, &t[triangleCount].v2, &t[triangleCount].v3, &t[triangleCount].v4);
				  triangleCount++;
			  }   
		}   
	}

	fclose(fp);

	float scale = 2.00f;
	  
	glBegin(GL_POLYGON);

	for (int i=0; i<triangleCount; i++)
	{
		glColor3f(0.5, 0.0, 0.5);
		glVertex3f(v[t[i].v1-1].x * scale, v[t[i].v1-1].y * scale, v[t[i].v1-1].z * scale);
		glVertex3f(v[t[i].v2-1].x * scale, v[t[i].v2-1].y * scale, v[t[i].v2-1].z * scale);
		glVertex3f(v[t[i].v3-1].x * scale, v[t[i].v3-1].y * scale, v[t[i].v3-1].z * scale);
		if(t[i].v4 >= 0 && t[i].v4 <= 30)
			glVertex3f(v[t[i].v4-1].x * scale, v[t[i].v4-1].y * scale, v[t[i].v4-1].z * scale);
	}

	glEnd();

	glFlush();
	glTranslatef(0, -200, 0);
}*/

void Renderer::updateScreen()
{
	//glFlush();
	SwapBuffers(this->hdc);
	//glFinish();
}