#ifndef _HEADER_MACRO_
#define _HEADER_MACRO_
#pragma warning(push)

#define COMPTR(v) _com_ptr_t<_com_IIID<v,&__uuidof(v)>>


#ifdef _UNICODE
typedef std::wstring String;
typedef LPCWSTR LPCGFWCHAR;
typedef WCHAR GFWCHAR;
#else
typedef std::string String;
typedef LPCSTR LPCGFWCHAR;
typedef CHAR GFWCHAR;
#endif


#ifdef _Debug
#define DEBUG(v)v
#define RELEASE(v)
#else
#define DEBUG(v)
#define RELEASE(v)v


#endif
#pragma warning(pop)
#endif