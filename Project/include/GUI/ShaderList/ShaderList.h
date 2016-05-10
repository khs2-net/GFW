#ifndef _HEADER_GFW_SHADEROBJECT_
#define _HEADER_GFW_SHADEROBJECT_
#pragma warning(push)

namespace GFW {
namespace GUI {
class ShaderList : public GFW::GUI::QuickStart_App{
public:
	~ShaderList();
	static ShaderList &getInstance() {
		static ShaderList ins;
		return ins;
	}


	ULONG Draw();
protected:
private:
	ShaderList();
};
}
}

#pragma warning(pop)
#endif