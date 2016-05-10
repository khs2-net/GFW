#ifndef _HEADER_GFW_DEVICE_
#define _HEADER_GFW_DEVICE_
#pragma warning(push)
#include "./Device/DirectXDevice.h"
#include "./Device/WindowDevice.h"
/*
namespace GFW {

class Device {
public:
	~Device();
	static Device &getInstance() {
		static Device ins;
		return ins;
	}

	void set(String, _Device);
	void Begin(String);
	void End();

	ID3D11Device *getDevice();
	ID3D11DeviceContext *getContext();
protected:
private:
	Device();
	struct _Device {
		DX11Device dx;
		WindowDevice window;
	};
	_Device *Current;
	std::map<String, _Device> device;

	std::list<_Device*> stack;
	unsigned long stack_count;
};

ID3D11Device *DXDevice() {
	return Device::getInstance().getDevice();
}
ID3D11DeviceContext *DXContext() {
	return Device::getInstance().getContext();
}

}*/
#pragma warning(pop)
#endif