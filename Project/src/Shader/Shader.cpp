using namespace GFW;
using namespace std;

//Command_Shader
Command_Shader::Command_Shader() {

}
Command_Shader::~Command_Shader() {

}

//後で処理をきれいに修正する
ULONG Command_Shader::Run(vector<string> argv) {
	GFW::GUI::Console &con = GFW::GUI::Console::getInstance();
	Shader &sh = Shader::getInstance();
	if (argv.size() < 3) {
		con.AddLog("Error argv \n");
		return -1;
	}
	ULONG type = 0;

	if (!argv[2].compare("pix")) {
		type = 1;
	} else if (!argv[2].compare("ver")) {
		type = 2;
	} else {
		con.AddLog("Error Command : " + argv[2] + "\n");
		return -1;
	}


	if (!argv[1].compare("set")) {
		if(type==1){
			if(sh.SetPixelShader(argv[3])){
				con.AddLog("Error \n");
				return -1;
			}
		}else if(type == 2){
			if(sh.SetVertexShader(argv[3])){
				con.AddLog("Error \n");
				return -1;
			}
		}
	} else if (!argv[1].compare("load")) {
		if (argv.size() < 5) {
			con.AddLog("Error argv \n");
			return -1;
		}
		if(type==1){
			if(sh.LoadPixelShader(argv[3],argv[4], argv[5], argv[6])){
				con.AddLog("Error \n");
				return -1;
			}
		}else if(type == 2){
			if(sh.LoadVertexShader(argv[3],argv[4], argv[5], argv[6])){
				con.AddLog("Error \n");
				return -1;
			}
		}
	} else if (!argv[1].compare("rem")) {
		if(type==1){
			if(sh.RemovePixelShader(argv[3])){
				con.AddLog("Error \n");
				return -1;
			}
		}else if(type == 2){
			if(sh.RemoveVertexShader(argv[3])){
				con.AddLog("Error \n");
				return -1;
			}
		}
	} else {
		con.AddLog("Error Command : "+argv[1] + "\n");
		return -1;
	}






	return 0;
}
ULONG Command_Shader::Help(vector<string> argv) {
	return 0;
}

Shader::Shader() {
	GFW::GUI::Console &con = GFW::GUI::Console::getInstance();
	static Command_Shader cs;
	con.AttachCommand("shader", cs);
	con.AttachCommand("sh", cs);
}
Shader::~Shader() {
	for (auto &v : this->pixsh) {
		v.second->Release();
	}
	for (auto &v : this->versh) {
		v.second->Release();
	}
	this->pixsh.clear();
	this->versh.clear();
}

ULONG Shader::FindPixelShader(std::string name){
	if(this->pixsh.find(name)!=this->pixsh.end()){
		return 1;
	}
	return 0;
}
ULONG Shader::FindVertexShader(std::string name){
	if(this->versh.find(name)!=this->versh.end()){
		return 1;
	}
	return 0;
}

ULONG Shader::LoadPixelShader(std::string name, std::string func, std::string model, std::string pass){
	GFW::DX11Device &device = GFW::DX11Device::getInstance();
	if(this->FindPixelShader(name)){
		return -1;
	}
	ID3D10Blob *buf;
	D3DX11CompileFromFileA(pass.c_str(), 0, 0, func.c_str(), model.c_str(), 0, 0, 0, &buf,0,0);
	ID3D11PixelShader *psmain_buf;
	device.getDevice()->CreatePixelShader(buf->GetBufferPointer(), buf->GetBufferSize(), nullptr, &psmain_buf);
	this->pixsh[name] = psmain_buf;

	return 0;
}
ULONG Shader::SetPixelShader(std::string name){
	GFW::DX11Device &device = GFW::DX11Device::getInstance();
	if(!this->FindPixelShader(name)){
		return -1;
	}
	device.getContext()->PSSetShader(this->pixsh[name], 0, 0);
	return 0;
}
ULONG Shader::RemovePixelShader(std::string name){
	if(!this->FindPixelShader(name)){
		return -1;
	}
	this->pixsh[name]->Release();
	this->pixsh.erase(name);
	return 0;
}
ULONG Shader::AttachPixelShader(std::string name, ID3D11PixelShader *sh) {
	if(this->FindPixelShader(name)){
		return -1;
	}
	this->pixsh[name] = sh;
	return 0;
}

ID3D11PixelShader* Shader::getPixelShader(std::string str) {
	if (!this->FindPixelShader(str)) {
		return nullptr;
	}
	return this->pixsh[str];
}

ULONG Shader::LoadVertexShader(std::string name, std::string func, std::string model, std::string pass){
	GFW::DX11Device &device = GFW::DX11Device::getInstance();
	if(this->FindVertexShader(name)){
		return -1;
	}
	ID3D11VertexShader *vsmain_buf;
	ID3D10Blob *buf;
	D3DX11CompileFromFileA(pass.c_str(), 0, 0, func.c_str(), model.c_str(), 0, 0, 0, &buf,0,0);
	device.getDevice()->CreateVertexShader(buf->GetBufferPointer(), buf->GetBufferSize(), nullptr, &vsmain_buf);
	this->versh[name] = vsmain_buf;
	return 0;
}
ULONG Shader::SetVertexShader(std::string name){
	GFW::DX11Device &device = GFW::DX11Device::getInstance();
	if(!this->FindVertexShader(name)){
		return -1;
	}
	device.getContext()->VSSetShader(this->versh[name], 0, 0);
	return 0;
}
ULONG Shader::RemoveVertexShader(std::string name){
	if(!this->FindVertexShader(name)){
		return -1;
	}
	this->versh[name]->Release();
	this->versh.erase(name);
	return 0;
}
ULONG Shader::AttachVertexShader(std::string name, ID3D11VertexShader *sh) {
	if (this->FindVertexShader(name)) {
		return -1;
	}
	this->versh[name] = sh;
	return 0;
}
ID3D11VertexShader* Shader::getVertexShader(std::string str) {
	if (!this->FindVertexShader(str)) {
		return nullptr;
	}
	return this->versh[str];
}
//
//Shader読み込み
//sh load $type $name pass
//
//Shader破棄
//sh rem $type $name
//
//Shaderセット(要修正(オブジェクト事で修正必要))
//sh set $type $name
//
//
//$type = {
//	pix,
//	ver,
//}
//
//$name = freename