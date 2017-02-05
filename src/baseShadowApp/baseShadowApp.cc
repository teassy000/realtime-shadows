#include "baseShadowApp.h"

#include <cassert>

//-----------------------------------------------------
BaseShadowApp::BaseShadowApp(HINSTANCE hinstance, std::string windowName)
	: hInstance_(hinstance)
	, windowName_(windowName)
{
}

//-----------------------------------------------------
BaseShadowApp::~BaseShadowApp()
{

}

//-----------------------------------------------------
bool BaseShadowApp::init()
{
	{ 
		bool res = initWindow();
		assert(res);
		if (!res)
			return false;
	}

	{

		bool res = d3dclass_.init(hwnd_);
		assert(res);
		if (!res)
			return false;
	}

	return true;
}

//-----------------------------------------------------
static LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------
bool BaseShadowApp::initWindow()
{
	// Register the window class.
	const char CLASS_NAME[] = "shadow app window";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance_;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	hwnd_ = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		windowName_.c_str(),			// Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,			// Parent window    
		NULL,			// Menu
		hInstance_,		// Instance handle
		NULL			// Additional application data
	);

	if (hwnd_ == nullptr)
	{
		return false;
	}
	
	ShowWindow(hwnd_, SW_SHOWNORMAL);
	
	return true;
}

//-----------------------------------------------------
void BaseShadowApp::render()
{
	d3dclass_.render();
}

//-----------------------------------------------------
void BaseShadowApp::release()
{
	d3dclass_.release();
}

//-----------------------------------------------------
int BaseShadowApp::run()					// -virtual
{
	// initialize
	if (!init())
		return -1;

	// Run the main loop.
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		render();
	}

	// release 
	release();

	return 0;
}


