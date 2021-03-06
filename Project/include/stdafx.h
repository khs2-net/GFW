#ifndef _HEADER_STDAFX_
#define _HEADER_STDAFX_
#pragma warning(push)

#pragma warning(disable:4996)
#pragma warning(disable:4838)

#include <d3d11_1.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <comip.h>
#include <string>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>
#include <Config.h>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <macro.h>
#include <./Type/Type.h>

#include <RenderObject/RenderObject.h>
#include <Math/Math.h>
#include <Device.h>
#include <Resource.h>
#include <GUI.h>
#include <xnamath.h>

#include <Shader.h>

#pragma warning(pop)
#endif
