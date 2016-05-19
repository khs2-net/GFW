#ifndef _HEADER_GFW_GUI_POPITEM_
#define _HEADER_GFW_GUI_POPITEM_
#pragma warning(push)
namespace GFW {
namespace GUI {
class _PopItem {
	friend class PopItem;
public:
	_PopItem();
	~_PopItem();

protected:
private:
	struct pos{
		float x, y;
	};
};
class PopItem :GFW::_Gui{
public:
	~PopItem();
	static PopItem &getInstance() {
		static PopItem ins;
		return ins;
	}
	ULONG Update();
	ULONG Draw();

	bool isDrag() {
		return this->drag;
	}
	bool isItem() {
		return this->item;
	}
protected:
private:
	PopItem();
	std::list<_PopItem*> obj;

	bool drag,item;

};


}
}

#pragma warning(pop)
#endif