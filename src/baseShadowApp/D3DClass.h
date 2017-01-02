#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


class D3DClass
{
private:
	IDXGISwapChain*			swapchain_{ nullptr };

	ID3D11Device*			device_{ nullptr };
	ID3D11DeviceContext*	context_{ nullptr };
	ID3D11RenderTargetView* rtv_{ nullptr };

public:
	D3DClass();
	~D3DClass();

	bool init(HWND hwnd);
	void render();
	void release();

private:

};
