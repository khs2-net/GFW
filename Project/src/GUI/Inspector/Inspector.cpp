using namespace GFW::GUI;

Inspector::Inspector() {
	this->func = nullptr;
	this->ptr = nullptr;
}
Inspector::~Inspector() {

}
ULONG Inspector::Attach(ULONG (*func)(void*), void *ptr) {
	this->func = func;
	this->ptr = ptr;
	return 0;
}

ULONG Inspector::Draw() {
	if (!this->viewflg)
		return 0;

	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiSetCond_FirstUseEver);
	//ImGui::SetNextWindowPos(ImVec2(0, 0));
	if (!ImGui::Begin("Inspector", &this->viewflg)) {
		ImGui::End();
		return 0;
	}

	if (this->func) {
		if (this->func(this->ptr)) {
			this->func = nullptr;
			this->ptr = nullptr;
		}
	}
	ImGui::End();
	return 0;
}