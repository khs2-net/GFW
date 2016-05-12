#pragma warning(disable:4996)
using namespace GFW::GUI;
using namespace std;




//--------------- QuickStart ---------------//
QuickStart::QuickStart() {
	this->openevent = false;
}
QuickStart::~QuickStart() {

}

ULONG QuickStart::AttachApp(string str, QuickStart_App& app) {
	if (this->apps.find(str) != this->apps.end()) {
		return(ULONG) -1;
	}
	this->apps[str] = &app;
	return 0;
}
ULONG QuickStart::RemoveApp(string str) {
	if (this->apps.find(str) == this->apps.end()) {
		return(ULONG) -1;
	}
	this->apps.erase(str);
	return 0;
}

ULONG QuickStart::Run(string str) {
	if (this->apps.find(str) == this->apps.end()) {
		return (ULONG) -1;
	}
	this->apps[str]->ViewSwitch();
	return 0;
}

int QuickStart_TextEditCallbackStub(ImGuiTextEditCallbackData* data) {
	return 0;
}
ULONG QuickStart::Draw() {
	ImGuiIO& io = ImGui::GetIO();
	if (io.KeyCtrl && io.KeysDown['Q']) {
		ImGui::OpenPopup("QuickStart");
		this->openevent = true;
	}
	if (ImGui::BeginPopup("QuickStart")){

		if (!ImGui::GetWindowIsFocused()) {
			ImGui::OpenPopup("QuickStart");
		}
		ImGui::Text("QuickStart");
		ImGui::Separator();
		if (this->openevent) { 
			this->openevent = false;
			ImGui::SetKeyboardFocusHere(1);
			strcpy(this->cmdbuf, "");
		}
		if (ImGui::InputText("", this->cmdbuf, sizeof(this->cmdbuf) / sizeof(this->cmdbuf[0]), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &QuickStart_TextEditCallbackStub, (void*)this)){
			char* input_end = this->cmdbuf + strlen(this->cmdbuf);
			while (input_end > this->cmdbuf && input_end[-1] == ' ') input_end--; *input_end = 0;
			if (this->cmdbuf[0]) {
				ULONG run_ret = this->Run(this->cmdbuf);
				if (run_ret == (ULONG)-1) {

				} else {
					ImGui::SetNextWindowFocus();
					ImGui::OpenPopup("QuickStart");
				}
			}
			strcpy(this->cmdbuf, "");
		}
		//Œó•âŒŸõ‚Æ‘I‘ð‚©‚çŽÀs‚Å‚«‚é‚æ‚¤‚É‚·‚é

		if (*this->cmdbuf) {
			std::string str(this->cmdbuf);
			static std::vector<const char*> items;
			items.clear();
			for (auto &v : this->apps) {
				int i = (int)v.first.find(str);
				if (!i) {
					items.push_back(v.first.c_str());
				}
			}
			if (items.size() > 0) {
				static int select = 0;
				ImGui::ListBox("", &select, &items[0],(int) items.size());
				if (io.KeysDown[ImGuiKey_DownArrow]) {
					strcpy(this->cmdbuf, items[select]);
				}
			}
		}
		ImGui::EndPopup();
	}
	return 0;
}