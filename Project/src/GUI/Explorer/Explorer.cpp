#pragma warning(disable:4996)
using namespace GFW::GUI;


Explorer::Explorer() {
	this->viewflg = true;
	QuickStart::getInstance().AttachApp("explorer", *this);
	QuickStart::getInstance().AttachApp("exp", *this);
	GFW::Gui::getInstance().Attach(this);

	boost::property_tree::ptree &pt = Config::get();


	if (boost::optional<std::string> value = pt.get_optional<std::string>("Explorer.CurrentDir")) {
		this->current_path = value.get();
	} else {
		this->current_path = this->getCurrentPath();
	}
	strcpy(this->inp_buff, this->current_path.c_str());

}
Explorer::~Explorer() {
	boost::property_tree::ptree &pt = Config::get();
	pt.put("Explorer.CurrentDir", this->current_path.c_str());

}

int Explorer_TextEditCallbackStub(ImGuiTextEditCallbackData* data) {
	return 0;
}

ULONG Explorer::Update() {
	return 0;
}
ULONG Explorer::Draw() {
	ULONG ret = 0;
	if (!this->viewflg) {
		return 0;
	}

	if (!ImGui::Begin("Explorer", &this->viewflg)) {
		ImGui::End();
		return ret;
	}
	
	

	if (ImGui::InputText("", this->inp_buff, _MAX_PATH, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &Explorer_TextEditCallbackStub, (void*)this)) {
		this->current_path = this->inp_buff;
	}



	if (ImGui::Button("...")) {
		size_t s = this->current_path.find_last_of('\\');
		this->current_path.erase(s,this->current_path.size()-s);
		if (this->current_path.size() <= 3) {
			this->current_path += "\\";
		}
	}
	const boost::filesystem::path path(this->current_path);

	BOOST_FOREACH(const boost::filesystem::path& p, std::make_pair(boost::filesystem::directory_iterator(path),
				  boost::filesystem::directory_iterator())) {
		if (boost::filesystem::is_directory(p)) {
			if(ImGui::Button((char*)p.filename().generic_string().c_str())) {
				this->current_path +='\\'+ p.filename().generic_string();
			}
		}
		if (!boost::filesystem::is_directory(p)) {
			if (ImGui::Button((char*)p.filename().generic_string().c_str())) {
			}
		}
	}

	ImGui::End();

	return 0;
}

ULONG Explorer::AttachExtension(std::string extension, ExplorerFileCall* _class) {
	if (this->extension.find(extension) == this->extension.end()) {
		return -1;
	}
	this->extension[extension] = _class;

	return 0;
}
std::string Explorer::getCurrentPath() {
	TCHAR path[_MAX_PATH];
	::GetCurrentDirectory(sizeof path,path);
	std::string str(path);
	return str;
}