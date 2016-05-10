#ifndef _HEADER_GFW_GUI_INSPECTOR_
#define _HEADER_GFW_GUI_INSPECTOR_
#pragma warning(push)
namespace GFW {
namespace GUI {
class Inspector : public QuickStart_App{
public:
	~Inspector();
	static Inspector &getInstance() {
		static Inspector ins;
		return ins;
	}

	ULONG Attach(ULONG (*func)(void*),void *ptr);
	ULONG Draw();
protected:
private:
	Inspector();
	ULONG (*func)(void*);
	void *ptr;
};
}
}

#pragma warning(pop)
#endif