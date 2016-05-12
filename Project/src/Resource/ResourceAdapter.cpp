using namespace GFW;

template<typename T>
Adapter<T>::Adapter() {
	this->ptr = nullptr;
}

template<typename T>
Adapter<T>::Adapter(const Adapter &a) {
	(*a.ptr)->AddRef();
	this->ptr = a.ptr;
}

template<typename T>
Adapter<T>::Adapter(String str) {
	//ResourceManager &rm = ResourceManager::getInstance();
	//this->ptr = rm.get(str);
}

template<typename T>
Adapter<T>::~Adapter() {
	//�Q�ƃJ�E���^���Z
	(*this->ptr)->Release();
}
