#ifndef _HEADER_GFW_RESOURCEOBJECT_
#define _HEADER_GFW_RESOURCEOBJECT_
#pragma warning(push)

namespace GFW {

template<typename T>
class ResourceObject {
public:
	//ResourceObject();
	//~ResourceObject();
protected:
	COMPTR(T) obj_ptr;
	String file;
	String name;
private:
};
}

#pragma warning(pop)
#endif