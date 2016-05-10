#ifndef _HEADER_GFW_GUI_DEFAULTCOMMAND_
#define _HEADER_GFW_GUI_DEFAULTCOMMAND_
#pragma warning(push)

//ä«óùÇÃÇ›ï`âÊÇÕÇ»Çµ(âºï`âÊÇ™ç°ì¸Ç¡ÇƒÇÈÅj


namespace GFW {
namespace GUI {
namespace Default {


	ULONG Init_Commands();
	class Command_InitCommands final : public Command {
	public:
		Command_InitCommands();
		~Command_InitCommands();
		ULONG Run(std::vector<std::string> argv);
		ULONG Help(std::vector<std::string> argv);
	};
	class Command_Help final : public Command {
	public:
		Command_Help();
		~Command_Help();
		ULONG Run(std::vector<std::string> argv);
		ULONG Help(std::vector<std::string> argv);
	};
	class Command_Remove final : public Command {
	public:
		Command_Remove();
		~Command_Remove();
		ULONG Run(std::vector<std::string> argv);
		ULONG Help(std::vector<std::string> argv);
	};

	//for
	//
	class Command_For final : public Command {
	public:
		Command_For();
		~Command_For();
		ULONG Run(std::vector<std::string> argv);
		ULONG Help(std::vector<std::string> argv);
	};
}
}
}


#pragma warning(pop)
#endif