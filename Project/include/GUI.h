#ifndef _HEADER_GFW_GUI_
#define _HEADER_GFW_GUI_
#pragma warning(push)

namespace GFW {
class _Gui {
public:
	virtual ULONG Update() = 0;
	virtual ULONG Draw() = 0;
};
class Gui {
public:
	~Gui();
	static Gui &getInstance() {
		static Gui ins;
		return ins;
	}
	ULONG Attach(const _Gui*);
	ULONG Remove(const _Gui*);
	ULONG Update();
	ULONG Draw();
protected:
private:
	Gui();
	std::list<_Gui*> gui;
};
}


#include <./imgui/imgui.h>
#include <./imgui/imgui_impl_dx11.h>

#include <./GUI/Selector/Selector.h>
//ŠeGUI
#include <./GUI/QuickStart/QuickStart.h>
#include <./GUI/Console/Console.h>
#include <./GUI/PopItem/PopItem.h>
//DefaultCommand
#include <./GUI/Console/DefaultCommand/DefaultCommand.h>
#include <./GUI/QuickStart/DefaultQuickStart/DefaultQuickStart.h>

#include <./GUI/TextEditor/TextEditor.h>
#include <./GUI/ShaderList/ShaderList.h>

#include <./GUI/Inspector/Inspector.h>

#include <./GUI/Explorer/Explorer.h>

#pragma warning(pop)
#endif