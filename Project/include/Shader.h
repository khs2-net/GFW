#ifndef _HEADER_GFW_SHADER_
#define _HEADER_GFW_SHADER_
#pragma warning(push)
namespace GFW {

class Command_Shader final : public GFW::GUI::Command {
public:
	Command_Shader();
	~Command_Shader();
	ULONG Run(std::vector<std::string> argv);
	ULONG Help(std::vector<std::string> argv);
};







class Shader {
public:
	~Shader();
	static Shader &getInstance() {
		static Shader ins;
		return ins;
	}
	ULONG FindPixelShader(std::string name);
	ULONG LoadPixelShader(std::string name,std::string);
	ULONG SetPixelShader(std::string name);
	ULONG RemovePixelShader(std::string name);
	ULONG AttachPixelShader(std::string name, ID3D11PixelShader*);
	std::map<std::string, ID3D11PixelShader*> &getPixelShaderMap() { return this->pixsh; }
	ID3D11PixelShader* getPixelShader(std::string);

	ULONG FindVertexShader(std::string name);
	ULONG LoadVertexShader(std::string name, std::string);
	ULONG SetVertexShader(std::string name);
	ULONG RemoveVertexShader(std::string name);
	ULONG AttachVertexShader(std::string name, ID3D11VertexShader*);
	std::map<std::string, ID3D11VertexShader*> &getVertexShaderMap() { return this->versh; }
	ID3D11VertexShader* getVertexShader(std::string);


protected:
private:
	Shader();
	std::map<std::string, ID3D11VertexShader*> versh;
	std::map<std::string, ID3D11PixelShader*> pixsh;
};

}

#pragma warning(pop)
#endif