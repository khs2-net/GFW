#ifndef _HEADER_GFW_GUI_QUICKSTART_
#define _HEADER_GFW_GUI_QUICKSTART_
#pragma warning(push)

//現在各APPがシングルトンによる設計なのでタスクの導入するまでは表示非表示を切り替えるだけ
//タスクシステムができたらインスタンスの生成を行い（外部に任せるかも）タスクシステムに追加するだけ
namespace GFW {
namespace GUI {

class QuickStart_App : public GFW::_Gui, boost::noncopyable {
public:
	QuickStart_App() {
		this->viewflg = false;
	}
	virtual void ViewShow() {
		this->viewflg = true;
	}
	virtual void ViewHidden() {
		this->viewflg = false;
	}
	virtual void ViewSwitch() {
		this->viewflg = !this->viewflg;
	}
	virtual bool getView() {
		return this->viewflg;
	}
protected:
	bool viewflg;
};

class QuickStart : public GFW::_Gui{
public:
	static QuickStart &getInstance() {
		static QuickStart ins;
		return ins;
	}
	~QuickStart();

	ULONG AttachApp(std::string, QuickStart_App&);
	ULONG RemoveApp(std::string);

	ULONG Run(std::string);
	ULONG Update();
	ULONG Draw();

protected:
private:
	QuickStart();
	std::map<std::string, QuickStart_App*> apps;
	char cmdbuf[256];
	bool openevent;
};

}
}
#pragma warning(pop)
#endif