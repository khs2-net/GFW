#ifndef _HEADER_GFW_RENDEROBJECT_
#define _HEADER_GFW_RENDEROBJECT_
#pragma warning(push)
namespace GFW {
class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual ULONG setState();
	virtual ULONG setShader();

protected:
private:
	//RenderState
	ID3D11SamplerState		**ss;
	ID3D11BlendState		**bs;
	ID3D11RasterizerState	**rs;
	ID3D11InputLayout		**il;
	D3D_PRIMITIVE_TOPOLOGY	**primtive_topology;

	//シェーダー回り
	ID3D11VertexShader		**vs;
	ID3D11HullShader		**hs;
	ID3D11DomainShader		**ds;
	ID3D11GeometryShader	**gs;
	ID3D11PixelShader		**ps;




};
}

#pragma warning(pop)
#endif