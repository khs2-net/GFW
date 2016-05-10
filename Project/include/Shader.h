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
	std::map<std::string, ID3D11PixelShader*> &getPixelShaderMap() { return this->pixsh; }

	ULONG FindVertexShader(std::string name);
	ULONG LoadVertexShader(std::string name, std::string);
	ULONG SetVertexShader(std::string name);
	ULONG RemoveVertexShader(std::string name);
	std::map<std::string, ID3D11VertexShader*> &getVertexShaderMap() { return this->versh; }


protected:
private:
	Shader();
	std::map<std::string, ID3D11VertexShader*> versh;
	std::map<std::string, ID3D11PixelShader*> pixsh;
};

}

#pragma warning(pop)
#endif