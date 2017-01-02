#include "D3DClass.h"

#include <DirectXMath.h>

#include "rtsp_utils.h"


#pragma comment (lib, "d3d11.lib")

//---------------------------------------
D3DClass::D3DClass()
{

}

//---------------------------------------
D3DClass::~D3DClass()
{
	release();
}

//---------------------------------------
bool D3DClass::init(HWND hwnd)
{
	assert(hwnd);
	HRESULT hr;

	// create device and swap chain
	{
		DXGI_SWAP_CHAIN_DESC scd{};

		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = hwnd;
		scd.SampleDesc.Count = 4;
		scd.Windowed = TRUE;

		const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		// create a device, device context and swap chain using the information in the scd struct
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,							// adapter		
			D3D_DRIVER_TYPE_HARDWARE,		// driver type
			NULL,							// software: only need to set while use software driver
			NULL,							// flag: indicate how d3d runs(debug, etc.)
			&featureLevel,					// (in)major feature level
			1,								// num of feature level
			D3D11_SDK_VERSION,				// SDK version 
			&scd,							// swap chain desc;
			&swapchain_,					// swap chain
			&device_,						// D3D device
			NULL,							// out feature level
			&context_);						// device context

		if (FAILED(hr))
			return false;
	}

	// setting render target
	{
		ID3D11Texture2D *bkbuffer;
		hr = swapchain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&bkbuffer);
		if (FAILED(hr))
			return false;

		hr = device_->CreateRenderTargetView(bkbuffer, NULL, &rtv_);
		bkbuffer->Release();
		if (FAILED(hr))
			return false;

		context_->OMSetRenderTargets(1, &rtv_, NULL);
	}

	// set viewport
	{
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = 1024;
		viewport.Height = 720;

		context_->RSSetViewports(1, &viewport);
	}

	return true;
}

//---------------------------------------
void D3DClass::render()
{
	const float color[4]{ 0.0f, 0.2f, 0.4f, 1.0f };
	context_->ClearRenderTargetView(rtv_, color);

	// do 3D rendering on the back buffer here

	swapchain_->Present(0, 0);
}

//---------------------------------------
void D3DClass::release()
{
	rts_safeRelease(swapchain_);
	rts_safeRelease(device_);
	rts_safeRelease(context_);
	rts_safeRelease(rtv_);
}

