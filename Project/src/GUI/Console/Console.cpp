#pragma warning(disable:4996)
using namespace GFW::GUI;
using namespace std;

//--------------- Command ---------------//

Command::Command() {

}
Command::~Command() {

}

ULONG Command::Run(vector<string> argv) {

	return 0;
}

ULONG Command::Help(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	con.AddLog("Unknown Command Help!\n");
	return 0;
}

//--------------- Console ---------------//

Console::Console() {
	this->viewflg = false;
}
Console::~Console() {

}


//Run
ULONG Console::Run(string cmdstr) {
	static vector<string> argv;
	boost::split(argv, cmdstr, boost::is_any_of(" "));
	if (argv.size() == 0) {
		this->AddLog("Unknown Command\n");
		return (ULONG) -1;
	}
	if (this->commands.find(argv[0]) == this->commands.end()) {
		this->AddLog(argv[0] + " is Unknown Command\n");
		return (ULONG) -2;
	}
	std::transform(argv[0].begin(), argv[0].end(), argv[0].begin(), ::tolower);

	this->AddLog(">>"+cmdstr + "\n");
	this->commands[argv[0]]->Run(argv);
	return 0;
}
ULONG Console::Help(string cmdstr) {
	static vector<string> argv;
	boost::split(argv, cmdstr, boost::is_any_of(" "));
	if (argv.size() == 0) {
		this->AddLog("Unknown Command\n");
		return (ULONG) -1;
	}
	if (this->commands.find(argv[0]) == this->commands.end()) {
		this->AddLog(argv[0] + " is Unknown Command\n");
		return (ULONG) -2;
	}
	std::transform(argv[0].begin(), argv[0].end(), argv[0].begin(), ::tolower);

	this->commands[argv[0]]->Help(argv);
	return 0;
}

//Command
ULONG Console::AttachCommand(string str, Command& cmd) {
	if (this->commands.find(str) != this->commands.end()) {
		return (ULONG) -1;
	}
	//std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	this->commands[str] = &cmd;
	this->cmdlist.push_back(str);
	return 0;
}
ULONG Console::RemoveCommand(string str) {
	this->commands.erase(str);
	this->cmdlist.remove(str);
	return 0;
}
list<string> &Console::getstrCommands() {
	return this->cmdlist;
}

//Log
ULONG Console::AddLog(string str) {
	this->log += str;
	this->ScrollToBottom = true;
	return 0;
}
ULONG Console::Clear() {
	this->log.clear();
	return 0;
}
//‰¼•`‰æ
int Console_TextEditCallbackStub(ImGuiTextEditCallbackData* data) {
	Console &con = Console::getInstance();
	return con.TextEditCallback(data);
}
int Console::TextEditCallback(ImGuiTextEditCallbackData* data) {
	//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
	//switch (data->EventFlag)
	//{
	//case ImGuiInputTextFlags_CallbackCompletion:
	//{
	//	// Example of TEXT COMPLETION
//
	//	// Locate beginning of current word
	//	const char* word_end = data->Buf + data->CursorPos;
	//	const char* word_start = word_end;
	//	while (word_start > data->Buf)
	//	{
	//		const char c = word_start[-1];
	//		if (c == ' ' || c == '\t' || c == ',' || c == ';')
	//			break;
	//		word_start--;
	//	}
//
	//	// Build a list of candidates
	//	ImVector<const char*> candidates;
	//	for (int i = 0; i < Commands.Size; i++)
	//		if (Strnicmp(Commands[i], word_start, (int) (word_end - word_start)) == 0)
	//			candidates.push_back(Commands[i]);
//
	//	if (candidates.Size == 0)
	//	{
	//		// No match
	//		AddLog("No match for \"%.*s\"!\n", (int) (word_end - word_start), word_start);
	//	}
	//	else if (candidates.Size == 1)
	//	{
	//		// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
	//		data->DeleteChars((int) (word_start - data->Buf), (int) (word_end - word_start));
	//		data->InsertChars(data->CursorPos, candidates[0]);
	//		data->InsertChars(data->CursorPos, " ");
	//	}
	//	else
	//	{
	//		// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
	//		int match_len = (int) (word_end - word_start);
	//		for (;;)
	//		{
	//			int c = 0;
	//			bool all_candidates_matches = true;
	//			for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
	//				if (i == 0)
	//					c = toupper(candidates[i][match_len]);
	//				else if (c != toupper(candidates[i][match_len]))
	//					all_candidates_matches = false;
	//			if (!all_candidates_matches)
	//				break;
	//			match_len++;
	//		}
//
	//		if (match_len > 0)
	//		{
	//			data->DeleteChars((int) (word_start - data->Buf), (int) (word_end - word_start));
	//			data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
	//		}
//
	//	}
//
	//	break;
	//}
	//}
	return 0;
}
ULONG Console::Draw() {//imgui_demo.cpp‚Æ‚Ù‚Ú“¯‚¶Š´‚¶(line:2177)
	if (!this->viewflg)
		return 0;
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin("Console", &this->viewflg)) {
		ImGui::End();
		return 0;
	}
	if (ImGui::Button("Clear")) this->Clear();
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	if (copy) ImGui::LogToClipboard();


	// Command-line
	if (ImGui::InputText("Input", this->cmdbuf, sizeof(this->cmdbuf) / sizeof(this->cmdbuf[0]), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &Console_TextEditCallbackStub, (void*)this))
	{
		char* input_end = this->cmdbuf + strlen(this->cmdbuf);
		while (input_end > this->cmdbuf && input_end[-1] == ' ') input_end--; *input_end = 0;
		if (this->cmdbuf[0])
			this->Run(this->cmdbuf);
		strcpy(this->cmdbuf, "");
	}
	// Demonstrate keeping auto focus on the input box
	if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::Separator();
	ImGui::SameLine();

	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::TextUnformatted(this->log.c_str());
	if (this->ScrollToBottom)
		ImGui::SetScrollHere(1.0f);
	this->ScrollToBottom = false;
	
	ImGui::EndChild();

	ImGui::End();
	
	return 0;
}