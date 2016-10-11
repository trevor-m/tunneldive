#include "GameWindow.h"

GameWindow::GameWindow()
{
	this->hdc = NULL;
	this->hwnd = NULL;
}

GameWindow::~GameWindow()
{
}

bool GameWindow::createWindow(std::string title, std::string classname, HINSTANCE hInstance, WNDPROC WndProc)
{
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
    wc.lpszClassName = TEXT(classname.c_str());
    wc.lpszMenuName = 0;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	RegisterClass(&wc);
	
	int width, height;
	RECT rect;
	width = WIDTH;
	height = HEIGHT;
	SetRect(&rect, 150, 150, WIDTH, HEIGHT);

    this->width = rect.right - rect.left;
    this->height = rect.bottom - rect.top;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	this->hwnd = CreateWindow(TEXT(classname.c_str()), TEXT(title.c_str()), WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if(this->hwnd == NULL)
    {
		return false;
    }
    ShowWindow(this->hwnd, SW_SHOW);
	this->hdc = GetDC(this->hwnd);
	return true;
}

bool GameWindow::messagePump()
{
	//Loops through all messages in queue
	while(PeekMessage(&this->msg, NULL, 0, 0, PM_REMOVE))
	{
		if(this->msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&this->msg);
		DispatchMessage(&this->msg);
	}
	return true;
}

bool GameWindow::destroyWindow()
{
	ReleaseDC(this->hwnd, this->hdc);
	return true;
}

HWND GameWindow::getHwnd()
{
	return this->hwnd;
}

HDC GameWindow::getHdc()
{
	return this->hdc;
}

int GameWindow::getWidth()
{
	return this->width;
}

int GameWindow::getHeight()
{
	return this->height;
}