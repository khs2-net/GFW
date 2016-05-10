using namespace GFW::GUI;

ShaderList::ShaderList() {

}
ShaderList::~ShaderList() {

}

struct ShaderListItem {
	std::string *str;
	void *ptr;
};
ULONG ShaderList_Inspector_Vertex(void *ptr) {
	ShaderListItem *sli = (ShaderListItem*)ptr;
	ID3D11VertexShader *vs = (ID3D11VertexShader*)sli->ptr;

	ImGui::Text("ItemType : VertexShader");
	ImGui::Separator();
	ImGui::SameLine();

	ImGui::Text("Name %s", sli->str->c_str());
	ImGui::Text("Ptr %x", sli->ptr);

	return 0;
}
ULONG ShaderList_Inspector_Pixel(void *ptr) {
	ShaderListItem *sli = (ShaderListItem*)ptr;
	ID3D11PixelShader *vs = (ID3D11PixelShader*)sli->ptr;

	ImGui::Text("ItemType : PixelShader");
	ImGui::Separator();
	ImGui::SameLine();

	ImGui::Text("Name %s", sli->str->c_str());
	ImGui::Text("Ptr %x", sli->ptr);

	return 0;
}


ULONG ShaderList::Draw() {
	ULONG ret = 0;
	ImGuiIO &io = ImGui::GetIO();
	GFW::Shader &sh = GFW::Shader::getInstance();
	GFW::GUI::Inspector &ins = GFW::GUI::Inspector::getInstance();
	if (!this->viewflg)
		return 0;
	if (!ImGui::Begin("ShaderList", &this->viewflg)) {
		ImGui::End();
		return ret;
	}
	std::map<std::string, ID3D11VertexShader*> &vs = sh.getVertexShaderMap();
	std::map<std::string, ID3D11PixelShader*> &ps = sh.getPixelShaderMap();
	static ShaderListItem sli;
	if (ImGui::TreeNode("Shader")) {
		if (ImGui::TreeNode("Vertex Shader")) {
			unsigned int i = 0;
			for (auto &v : vs) {
				if (ImGui::Button(v.first.c_str())) {
					//inspector‚Ö‚Ì“o˜^
					sli.str = (std::string*)&v.first;
					sli.ptr = v.second;
					ins.Attach(ShaderList_Inspector_Vertex, (void*)&sli);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Pixel Shader")) {
			unsigned int i = 0;
			for (auto &v : ps) {
				if (ImGui::Button(v.first.c_str())) {
					//inspector‚Ö‚Ì“o˜^
					sli.str = (std::string*)&v.first;
					sli.ptr = v.second;
					ins.Attach(ShaderList_Inspector_Pixel, (void*)&sli);
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}


	ImGui::End();

	return ret;
}