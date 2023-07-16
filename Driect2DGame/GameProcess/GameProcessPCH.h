#pragma once

#include <windows.h>
#include <iostream>

// 헤더 포함
#include <wincodec.h>
#include <d2d1.h>
//  구현이있는 라이브러리 포함
#pragma comment(lib, "d2d1.lib")

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <algorithm>

#include <string>
using std::string;
using std::wstring;
using std::make_pair;

#include <map>
using std::map;

#include <queue>
using std::queue;

#include <set>
using std::set;

#include "MathModuleHeader.h"
#include "RendererHeader.h"

#include "Define.h"
#include "UnitDefine.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
