#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <memory>

// this is copy form https://github.com/shobomaru/KinectV2Test
//! Custom deleter of std::unique_ptr for COM instance.
struct Deleter
{
	void operator()(IUnknown* com) {
		if (com) com->Release();
	}
};

class D3DClass
{
private:
	std::unique_ptr<IDXGISwapChain, Deleter>			swapChain_{ nullptr };
	std::unique_ptr<ID3D11Device, Deleter>				device_{ nullptr };
	std::unique_ptr<ID3D11DeviceContext, Deleter>		context_{ nullptr };
	std::unique_ptr<ID3D11RenderTargetView, Deleter>	rtv_{ nullptr };

	float* vertices;

public:
	D3DClass();
	~D3DClass();

	bool init(HWND hwnd);
	void render();
	void release();

private:
	bool initShaders();
	bool initModel();
};
