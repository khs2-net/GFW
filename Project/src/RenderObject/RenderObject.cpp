using namespace GFW;

RenderObject::RenderObject() {
	this->primtive_topology = nullptr;
}
RenderObject::~RenderObject() {

}


ULONG RenderObject::setState() {
	GFW::DX11Device &device = GFW::DX11Device::getInstance();


	device.getContext()->RSSetState(*this->rs);
	device.getContext()->IASetPrimitiveTopology(**this->primtive_topology);



	return 0;
}
ULONG RenderObject::setShader() {
	GFW::DX11Device &device = GFW::DX11Device::getInstance();

	device.getContext()->VSSetShader(*this->vs, 0, 0);
	device.getContext()->HSSetShader(*this->hs, 0, 0);
	device.getContext()->DSSetShader(*this->ds, 0, 0);
	device.getContext()->GSSetShader(*this->gs, 0, 0);
	device.getContext()->PSSetShader(*this->ps, 0, 0);


	return 0;
}