#ifndef _HEADER_GFW_PRIMITIVE_
#define _HEADER_GFW_PRIMITIVE_
#pragma warning(push)
namespace GFW {;
class Primitive {
public:
	Primitive();
	~Primitive();
protected:
private:
	COMPTR(ID3D11InputLayout) inputlayout;
	COMPTR(ID3D11Buffer) vex;
};

}

#pragma warning(pop)
#endif