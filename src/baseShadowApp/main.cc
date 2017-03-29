#include <windows.h>
#include "baseShadowApp.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	BaseShadowApp app(hInstance, L"base shadow app");

	return app.run();
}
