#ifndef _HEADER_GFW_DIRECTX_
#define _HEADER_GFW_DIRECTX_
#pragma warning(push)

namespace GFW {
class DX11Device :public boost::noncopyable {
public:
	virtual ~DX11Device();
	static DX11Device &getInstance() {
		static DX11Device ins;
		return ins;
	}

	unsigned long Init(HWND, unsigned long, unsigned long, bool);
	ID3D11Device *getDevice() {
		return this->device;
	}
	ID3D11DeviceContext *getContext() {
		return this->context;
	}
	IDXGISwapChain *getSwapChain() {
		return this->swapchain;
	}
#ifdef _Debug
	ID3DUserDefinedAnnotation *getAnotation() {
		return this->anotation;
	}
#endif
	ID3D11RenderTargetView *getRTV() { return this->rendertargetview; }
	ID3D11DepthStencilView *getDSV() { return this->depthstencilview; }
protected:
private:
	DX11Device();
	D3D_DRIVER_TYPE drivertype;
	D3D_FEATURE_LEVEL feature;
	COMPTR(ID3D11Device) device;
	//COMPTR(ID3D11VideoDevice) video;
	COMPTR(ID3D11DeviceContext) context;
	COMPTR(IDXGISwapChain) swapchain;
#ifdef _Debug
	COMPTR(ID3DUserDefinedAnnotation) anotation;
#endif

	COMPTR(ID3D11RenderTargetView)		rendertargetview;// �����_�[�^�[�Q�b�g�r���[
	COMPTR(ID3D11DepthStencilView)		depthstencilview;// �X�e���V���r���[
};
}
#pragma warning(pop)

#endif