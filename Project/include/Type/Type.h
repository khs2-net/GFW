#ifndef _HEADER_GFW_TYPE_
#define _HEADER_GFW_TYPE_
#pragma warning(push)


//ì∆é©ÇÃå^
namespace GFW {
namespace Type {




#ifdef DX11

//DX11
struct GFW_INPUT_ELEMENT_DESC : public D3D11_INPUT_ELEMENT_DESC{
	char _SemanticName[32];
};
struct GFW_INPUT_ELEMENT_DESC_ARRAY{//å„Ç©ÇÁóvèCê≥
	std::vector<GFW_INPUT_ELEMENT_DESC> value;
};

typedef D3D11_RASTERIZER_DESC GFW_RASTERIZER_DESC;
#endif
}
}

#pragma warning(pop)
#endif