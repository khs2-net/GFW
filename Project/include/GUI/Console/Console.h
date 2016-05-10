#ifndef _HEADER_GFW_GUI_CONSOLE_
#define _HEADER_GFW_GUI_CONSOLE_
#pragma warning(push)
//ŠÇ—‚Ì‚İ•`‰æ‚Í‚È‚µ(‰¼•`‰æ‚ª¡“ü‚Á‚Ä‚éj


namespace GFW {
namespace GUI {

class Command {
public:
	Command();
	virtual ~Command();
	virtual ULONG Run(std::vector<std::string> argv);
	virtual ULONG Help(std::vector<std::string> argv);
protected:
private:
};

class Console :public  QuickStart_App {
public:
	~Console();
	static Console &getInstance() {
		static Console ins;
		return ins;
	}

	//Command Run
	ULONG Run(std::string);
	ULONG Help(std::string);

	//Command
	ULONG AttachCommand(std::string, Command&);
	ULONG RemoveCommand(std::string);
	std::list<std::string> &getstrCommands();

	//Log
	ULONG AddLog(std::string);
	ULONG Clear();
	std::string &getLog() { return this->log; }

	//‰¼•`‰æ
	ULONG Draw();
	int TextEditCallback(ImGuiTextEditCallbackData* data);
protected:
private:
	Console();
	std::map<std::string, Command*> commands;
	std::list<std::string> cmdlist;
	std::string log;
	char cmdbuf[256];

	//‰¼•`‰æ—p
	bool ScrollToBottom;
};

}
}


#pragma warning(pop)
#endif