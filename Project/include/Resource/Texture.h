#ifndef _HEADER_GFW_TEXTURE_
#define _HEADER_GFW_TEXTURE_
#pragma warning(push)

namespace GFW {
/*
class Texture1D : public ResourceObject<ID3D11Texture1D> {
public:
	Texture1D();
	~Texture1D();

	ULONG Create(UINT, D3D11_USAGE, DXGI_FORMAT, UINT = D3D11_BIND_SHADER_RESOURCE, UINT CPU_ACCESS_FLAG = 0, UINT = 0);
	ULONG LoadFile(String file);

	ID3D11Texture1D				*getTex() { return tex; }
	ID3D11ShaderResourceView	*getSRV() { return srv; }
	ID3D11RenderTargetView		*getRTV() { return rtv; }
protected:
private:
	COMPTR(ID3D11Texture1D)				tex;
	COMPTR(ID3D11ShaderResourceView)	srv;
	COMPTR(ID3D11RenderTargetView)		rtv;

};
*/
class Texture2D : public ResourceObject<ID3D11Texture2D> {
public:
	Texture2D();
	~Texture2D();

	ULONG Create(UINT, UINT, D3D11_USAGE, DXGI_FORMAT, UINT = D3D11_BIND_SHADER_RESOURCE, UINT CPU_ACCESS_FLAG = 0);
	ULONG LoadFile(String file);

	ID3D11Texture2D				*getTex() { return tex; }
	ID3D11ShaderResourceView	*getSRV() { return srv; }
	ID3D11RenderTargetView		*getRTV() { return rtv; }
protected:
private:
	COMPTR(ID3D11Texture2D)				tex;
	COMPTR(ID3D11ShaderResourceView)	srv;
	COMPTR(ID3D11RenderTargetView)		rtv;
};
/*
class Texture3D : public ResourceObject<ID3D11Texture3D> {
public:
	Texture3D();
	~Texture3D();

	ULONG Create(UINT, UINT, UINT, D3D11_USAGE, DXGI_FORMAT,UINT , UINT = D3D11_BIND_SHADER_RESOURCE, UINT CPU_ACCESS_FLAG = 0);
	ULONG LoadFile(String file);

	ID3D11Texture3D				*getTex() { return tex; }
	ID3D11ShaderResourceView	*getSRV() { return srv; }
	ID3D11RenderTargetView		*getRTV() { return rtv; }
protected:
private:
	ID3D11Texture3D				*tex;
	ID3D11ShaderResourceView	*srv;
	ID3D11RenderTargetView		*rtv;
};
*/
}

#pragma warning(pop)
#endif