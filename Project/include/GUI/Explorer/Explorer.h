#ifndef _HEADER_GFW_GUI_EXPLORER_
#define _HEADER_GFW_GUI_EXPLORER_
#pragma warning(push)
namespace GFW {
namespace GUI {

class ExplorerFileCall : public _Gui {
public:
	virtual ~ExplorerFileCall() = 0;

	virtual ULONG Update() = 0;
	virtual ULONG Draw() = 0;

	virtual ULONG onDoubleRightClick(std::string filepass) = 0;
	virtual ULONG onRightClick(std::string filepass) = 0;

	virtual ULONG onDoubleLeftClick(std::string filepass) = 0;
	virtual ULONG onLeftClick(std::string filepass) = 0;

protected:
private:
};

class Explorer : public GFW::GUI::QuickStart_App{
public:
	~Explorer();
	static Explorer &getInstance() {
		static Explorer ins;
		return ins;
	}
	ULONG Update();
	ULONG Draw();

	ULONG AttachExtension(std::string, ExplorerFileCall*);
protected:
private:
	std::map<std::string,ExplorerFileCall*> extension;
	std::string getCurrentPath();//ç°å„APIÇ∆ÇµÇƒÇ‹Ç∆ÇﬂÇÁÇÍÇÈÇ»ÇÁÇ‹Ç∆ÇﬂÇÈ(ExplorerClassÇÃíÜÇ…íuÇ≠ïKóvÇ»Çµ)
	Explorer();

	std::string current_path;
	TCHAR inp_buff[_MAX_PATH];
};

}
}
#include "./DefaultExtension/DefaultExtension.h"
#pragma warning(pop)
#endif