#pragma once

// 렌더러에 필요한 헤더파일

#include <string>
using std::wstring;

#include <map>
using std::map;

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <d2d1_1.h>

#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")
#include <assert.h>
#include <d2d1helper.h>

#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib") // WIC

using namespace D2D1;

#include "MathModuleHeader.h"