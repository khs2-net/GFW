using namespace GFW;



Gui::Gui() {

	ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("./resrc/fonts/meiryo.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	io.Fonts->AddFontFromFileTTF("./resrc/fonts/ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
}
Gui::~Gui() {

}


ULONG Gui::Attach(const _Gui *g){
	if (!g)
		return (ULONG)-1;
	for (auto &v : this->gui) {
		if (v == g) {
			return (ULONG)-2;
		}
	}
	this->gui.push_back((_Gui*)g);
	return 0;
}
ULONG Gui::Remove(const _Gui *g){
	this->gui.remove((_Gui*)g);
	return 0;
}

ULONG Gui::Draw() {
	for (auto &v : this->gui) {
		v->Draw();
	}
	return 0;
}