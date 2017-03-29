#include "D3DClass.h"

#include <DirectXMath.h>
#include <Model.h>

#include <memory>

#pragma comment (lib, "d3d11.lib")
using namespace DirectX;
using namespace std;

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

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;
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
			&swapChain,						// swap chain
			&device,						// D3D device
			NULL,							// out feature level
			&context);						// device context

		if (FAILED(hr))
			return false;

		swapChain_.reset(swapChain);
		device_.reset(device);
		context_.reset(context);
	}

	// setting render target
	{
		ID3D11Texture2D *bkbuffer;
		ID3D11RenderTargetView* rtv;
		hr = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&bkbuffer);
		if (FAILED(hr))
			return false;

		hr = device_->CreateRenderTargetView(bkbuffer, NULL, &rtv);
		if (FAILED(hr))
			return false;
		rtv_.reset(rtv);
		bkbuffer->Release();

		context_->OMSetRenderTargets(1, &rtv, NULL);
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
	context_->ClearRenderTargetView(rtv_.get(), color);

	// do 3D rendering on the back buffer here

	swapChain_->Present(0, 0);
}

//---------------------------------------
void D3DClass::release()
{

}

//---------------------------------------
bool D3DClass::initShaders()
{

	return false;
}

//---------------------------------------
bool D3DClass::initModel(const wchar_t* filename)
{
	auto model = Model::CreateFromVBO(device_.get(), filename);

	return true;
}

