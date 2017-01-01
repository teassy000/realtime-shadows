// this class would :
// 1> create a window
// 2> manage a DirectX class
// 3> manage camera 
// 4> manage light and other resources

#pragma once

#include <windows.h>
#include <iostream>


class BaseShadowApp
{
private:
	// window stuffs
	HWND hwnd_{nullptr};
	HINSTANCE hInstance_{nullptr};
	std::string windowName_{ "default window name" };

	// direct3d stuff

	// camera

	// light

public:
	BaseShadowApp(HINSTANCE, std::string);
	~BaseShadowApp();

	bool init();
	void render();
	void release();

	virtual int run();

private:
	bool initWindow();
};

