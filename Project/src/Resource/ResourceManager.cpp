using namespace GFW;
//
//template<typename T>
//ResourceManager<T>::ResourceManager() {
//
//}
//
//template<typename T>
//ResourceManager<T>::~ResourceManager() {
//
//}
//
//template<typename T>
//ULONG ResourceManager<T>::Release() {
//	for (auto &v : this->obj) {
//		if (v) {
//			v->Release();
//		}
//	}
//	return 0;
//}
//template<typename T>
//ULONG ResourceManager<T>::Release(const T& data) {
//	static ResourceManager<T> &rm = ResourceManager<T>::getInstance<T>();
//
//	return 0;
//}
//
//template<typename T>
//ULONG Adapter<T>::Attach(const T& data) {
//
//	return 0;
//}