#ifndef _HEADER_GFW_ADAPTER_
#define _HEADER_GFW_ADAPTER_
#pragma warning(push)
namespace GFW {

template<typename T>
class Adapter {
public:
	Adapter();
	Adapter(const Adapter&);
	Adapter(String str);

	~Adapter();
	T *operator->() {
		return *this->ptr;
	}
protected:
private:
	T **ptr;
};
}

#pragma warning(pop)
#endif