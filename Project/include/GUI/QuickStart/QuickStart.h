#ifndef _HEADER_GFW_GUI_QUICKSTART_
#define _HEADER_GFW_GUI_QUICKSTART_
#pragma warning(push)

//���݊eAPP���V���O���g���ɂ��݌v�Ȃ̂Ń^�X�N�̓�������܂ł͕\����\����؂�ւ��邾��
//�^�X�N�V�X�e�����ł�����C���X�^���X�̐������s���i�O���ɔC���邩���j�^�X�N�V�X�e���ɒǉ����邾��
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