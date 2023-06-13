// Entry.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "pch.h"
#include "Entry.h"
#include "RendererHeader.h"
#include "EngineHeader.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){
    D2DEngine* engine = new D2DEngine();

    engine->Initalize(hInstance, nCmdShow);

    engine->Process();

    engine->Finalize();


    return 0;
}

