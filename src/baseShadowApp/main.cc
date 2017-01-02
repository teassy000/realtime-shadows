#include <windows.h>
#include "baseShadowApp.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	BaseShadowApp app(hInstance, "base shadow app");

	return app.run();
}
