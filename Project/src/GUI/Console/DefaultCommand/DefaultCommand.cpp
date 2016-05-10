#pragma warning(disable:4996)
using namespace GFW::GUI::Default;
using namespace std;


//Default Command
ULONG GFW::GUI::Default::Init_Commands() {
	Console &con = Console::getInstance();
	static Command_InitCommands cmdini;
	static Command_Help help;
	static Command_Remove remove;
	static Command_For _for;
	con.AttachCommand("help", help);
	con.AttachCommand("remove", remove);
	con.AttachCommand("dinit", cmdini);
	con.AttachCommand("for", _for);
	return 0;
}
//--------------- Command_InitCommands ---------------//
Command_InitCommands::Command_InitCommands() {

}
Command_InitCommands::~Command_InitCommands() {

}
ULONG Command_InitCommands::Run(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	Init_Commands();
	return 0;
}
ULONG Command_InitCommands::Help(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	con.AddLog(argv[0] + " : Init Default Commands\n");
	return 0;
}
//--------------- Command_Help ---------------//
Command_Help::Command_Help() {

}
Command_Help::~Command_Help() {

}
ULONG Command_Help::Run(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	if (argv.size() == 1) {
		this->Help(argv);
		return 0;
	}
	con.Help(argv[1]);

	return 0;
}
ULONG Command_Help::Help(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	std::list<std::string> &cmds = con.getstrCommands();
	con.AddLog("Command List\n");
	for (auto &v : cmds) {
		con.AddLog(v + " ");
	}
	con.AddLog("\n");
	return 0;
}

//--------------- Command_Remove ---------------//
Command_Remove::Command_Remove() {

}
Command_Remove::~Command_Remove() {

}
ULONG Command_Remove::Run(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	for (auto &v : argv) {
		con.RemoveCommand(v);
	}
	return 0;
}
ULONG Command_Remove::Help(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	con.AddLog("remove : Remove Command\n");
	return 0;
}


//--------------- Command_For ---------------//
Command_For::Command_For() {

}
Command_For::~Command_For() {

}

ULONG Command_For::Run(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	if (argv.size() < 3) {
		return (ULONG)-1;
	}
	UINT cnt = std::atoi(argv[1].c_str());
	for (UINT i = 0; i < cnt; i++) {
		for (UINT ii = 2; ii < argv.size(); ii++) {
			con.Run(argv[ii]);
		}
	}
	return 0;
}
ULONG Command_For::Help(std::vector<std::string> argv) {
	Console &con = Console::getInstance();
	con.AddLog("for : For Command\n");
	return 0;
}