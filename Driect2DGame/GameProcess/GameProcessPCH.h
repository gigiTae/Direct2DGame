// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include <windows.h>
#include <iostream>

// 헤더 포함
#include <d2d1.h>
//  구현이있는 라이브러리 포함
#pragma comment(lib, "d2d1.lib")

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <string>
using std::string;
using std::wstring;
using std::make_pair;

#include <map>
using std::map;

#include <set>
using std::set;

#include "Define.h"

#include "MathModuleHeader.h"
#include "RendererHeader.h"


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
