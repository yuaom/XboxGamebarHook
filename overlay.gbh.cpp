// github.com/dysprsm

#include "overlay.h"
#include <comdef.h>
#include <corecrt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool Overlay::init()
{
    window = FindWindowA("XboxGameBarPoc_Mutex", "XboxGameBarPoc_SharedMemory");

    if (!window)
        return false;

    auto info = GetWindowLongA(window, -20);

    if (!info)
        return false;

    auto attrchange = SetWindowLongPtrA(window, -20, (LONG_PTR) (info | 0x20));

    if (!attrchange)
        return false;

    MARGINS margin;
    margin.cyBottomHeight = margin.cyTopHeight = margin.cxLeftWidth = margin.cxRightWidth = -1;

    if (DwmExtendFrameIntoClientArea(window, &margin) != S_OK)
        return false;

    if (!SetLayeredWindowAttributes(window, 0x000000, 0xFF, 0x02))
        return false;

    if (!SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, 0x0002 | 0x0001))
        return false;

    ShowWindow(window, SW_SHOW);

    return true;
}

bool Overlay::startup_d2d()
{
    RECT rc;
    if (HRESULT ret = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory) == S_OK)
    {
        if (ret = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**) (&write_factory)) == S_OK){
            write_factory->CreateTextFormat(font, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &format);
            GetClientRect(window, &rc);

            if (ret = d2d_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)), D2D1::HwndRenderTargetProperties(window, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &tar) == S_OK)
            {
                D2D1_BRUSH_PROPERTIES properties = {1.0f, D2D1::Matrix3x2F::Identity()};

                tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), properties, &brush);

                return true;
            }
        }
    }
    return false;
}

        void Overlay::begin_scene()
        {
            tar->BeginDraw();
        }

        void Overlay::end_scene()
        {
            tar->EndDraw();
        }

        void Overlay::clear_scene()
        {
            tar->Clear();
        }

        void Overlay::draw_text(int x, int y, const char* text, D2D1::ColorF color, ...)
        {
            char    buffer[4096];
            int     length;
            wchar_t out[256];
            RECT    window_metrics;

            if (!GetWindowRect(window, &window_metrics))
                return;

            va_list arg_list;
            va_start(arg_list, text);
            vsnprintf(buffer, sizeof(buffer), text, arg_list);
            va_end(arg_list);

            length = strlen(buffer);

            mbstowcs(out, buffer, length);

            brush->SetColor(color);
        }

        // for support dm me on discord!
        // damo#5555 - online 3PM - 1AM