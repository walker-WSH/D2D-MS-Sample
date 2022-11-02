// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#define Assert(a)

#include "RingBuffer.h"
#include "strsafe.h"

/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/

template<class Interface>
inline void
SafeRelease(
    Interface **ppInterfaceToRelease
    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/

namespace AnimationStyle
{
    enum Enum
    {
        None = 0,
        Translation = 1,
        Rotation = 2,
        Scaling = 4
    };
};

DEFINE_ENUM_FLAG_OPERATORS(AnimationStyle::Enum);

namespace TextRenderingMethod
{
    enum Enum
    {
        Default,
        Outline,
        UseA8Target,
        NumValues
    };
};

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    HRESULT Initialize();

    void RunMessageLoop();

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    void DiscardDeviceResources();

    HRESULT OnRender();

    void OnResize(
        UINT width,
        UINT height
        );

    HRESULT OnChar(
        SHORT key
        );

    void OnDestroy();

    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );

    BOOL IsRunning()
    {
        return m_fRunning;
    }

    void UpdateWindowText();

    HRESULT ResetAnimation(
        bool resetClock
        );

    void CalculateTransform(
        D2D1_MATRIX_3X2_F *pTransform
        );

private:
    DWORD m_startTime;
    AnimationStyle::Enum m_animationStyle;
    TextRenderingMethod::Enum m_renderingMethod;
    D2D1_POINT_2F m_overhangOffset;

    HWND m_hwnd;
    ID2D1Factory *m_pD2DFactory;
    IDWriteFactory *m_pDWriteFactory;
    ID2D1HwndRenderTarget *m_pRT;
    IDWriteTextFormat *m_pTextFormat;
    IDWriteTextLayout *m_pTextLayout;
    ID2D1SolidColorBrush *m_pBlackBrush;
    ID2D1BitmapRenderTarget *m_pOpacityRT;
    BOOL m_fRunning;

    RingBuffer<LONGLONG, 10> m_times;
};


