#ifndef _HEADER_GFW_WINDOW_
#define _HEADER_GFW_WINDOW_
#pragma warning(push)
namespace GFW {
class WindowDevice : public boost::noncopyable{
public:
	virtual ~WindowDevice();
	static WindowDevice &getInstance() {
		static WindowDevice ins;
		return ins;
	}
	unsigned long Init(HINSTANCE,int,String, unsigned long, unsigned long,bool = true);

	void setTitle(String);
	String getTitle();
	void ReSize(ULONG, ULONG);
	bool f() { return this->runflg; }
	ULONG MessageLoop(void(*function)(void) = nullptr);
protected:
private:
	WindowDevice();

	HWND handle;
	WNDCLASSEX wcex;
	String title;
	bool windowmode;
	UINT width, height;

	boost::thread thread;
	volatile bool runflg;
};
}

#pragma warning(pop)
#endif