using namespace GFW::GUI;



//%s/a/TestClass/g 
//%s/b/TestClass2/g






Text::Text() {
	this->text.push_back("test");
}
Text::~Text() {

}

///�t�@�C������n
//TODO �t�@�C���p�X�`�F�b�N�̎��� (�t�@�C���p�X�����݂��Ȃ��ꍇ�G���[�i�t���O�ˑ��j�j�t�@�C���p�X�����킩�ǂ���
ULONG Text::setFilePass(String filepass, ULONG flg) {
	ULONG ret = 0;
	this->filepass = filepass;//���݂̓`�F�b�N���ĂȂ�
	return ret;
}
String Text::getFilePass() {
	return this->filepass;
}

//TODO �t�@�C�����̃`�F�b�N�����ĂȂ��̂Ńf�B���N�g����ǉ��œ���邱�Ƃ��\ �e���v���[�g���ł��������̂Ō���C��
ULONG Text::setFileName(String filename) {
	ULONG ret = 0;

	//std::vector<String> str;
	//boost::split(str, this->filepass, boost::is_any_of(TEXT("\\/")));
	//this->filepass.clear();
	//*str.rbegin() = filepass;
	//for (auto &v : str) {
	//	this->filepass += v+TEXT("\\");
	//}
	return ret;
}
//���얢�m�F�����Ǔ����Ǝv��
String Text::getFileName() {
	std::vector<String> str;
	//boost::split(str, this->filepass, boost::is_any_of(TEXT("\\/")));
	return *str.rbegin();
}

ULONG Text::deleteFile() {
	this->text.clear();
	this->cursor = this->text.end();
	boost::filesystem::path path(this->filepass);
	boost::system::error_code error;
	bool ret = boost::filesystem::exists(path, error);
	if (!ret || error) {
		return -1;
	}
	else {
		boost::filesystem::remove(path);
	}
	return 0;
}

///�e�L�X�g����n
ULONG Text::New() {
	this->text.clear();
	this->cursor = this->text.end();
	return 0;
}
String Text::getAllString() {
	String str;
	for (auto &v : this->text) {
		str += v;
	}
	return str;
}





TextEditor::TextEditor() {
	this->view = true;
	this->current = this->textlist.end();
}
TextEditor::~TextEditor() {

}

ULONG TextEditor::newText(String title) {
	if (this->textlist.find(title) != this->textlist.end()) {
		return -1;
	}
	this->textlist[title].New();
	this->current = this->textlist.find(title);
	return 0;
}

//������
ULONG TextEditor::loadText(String pass) {
	return 0;
}
//������
ULONG TextEditor::saveText(String saveas) {

	return 0;
}
ULONG TextEditor::deleteText() {
	if (this->isCurrent()) {
		return -1;
	}
	this->current->second.deleteFile();
	this->removeText();
	return 0;
}
ULONG TextEditor::removeText() {
	if (this->isCurrent()) {
		return -1;
	}
	this->textlist.erase(this->current++);
	return 0;
}

String TextEditor::getAllText() {
	if (this->isCurrent()) {
		return TEXT("");
	}
	return this->current->second.getAllString();
}
std::list<String> &TextEditor::getList() {
	static std::list<String> list;
	list.clear();
	for (auto &v : this->textlist) {
		list.push_back(v.first);
	}
	return list;
}

void TextEditor::Update() {
	if (!this->view)
		return;

	ImGui::SetNextWindowPos(ImVec2(500, 20), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("TextEditor", &this->view, ImGuiWindowFlags_MenuBar);
	this->Update_Menu();

	ImGui::BeginChild("left pane", ImVec2(150, 0), true);
	for (std::map<String, Text>::iterator v = this->textlist.begin(); v != this->textlist.end(); v++) {
		if (ImGui::Selectable(v->first.c_str(), this->current == v)) {
			this->current = v;
		}
	}
	ImGui::EndChild();
	ImGui::SameLine();
	//ImGui::InputTextMultiline()
	//if(this->current != this->textlist.end()){
		//ImGui::Text("%s", this->current->second.getAllString().c_str());
	//}

	ImGui::End();
}
void TextEditor::Update_Menu() {
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("NewFile", nullptr)) {
				this->newText(TEXT("test") + rand());
			}
			if (ImGui::MenuItem("Save", nullptr)) {
				this->saveText();
			}
			if (ImGui::MenuItem("Delete File", nullptr)) {
				this->deleteText();
			}
			if (ImGui::MenuItem("Remove File", nullptr)) {
				this->removeText();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

ULONG TextEditor::isCurrent() {
	return this->current == this->textlist.end();
}