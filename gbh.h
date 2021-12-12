#pragma once
#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <string>
#include <vector>
#include <windows.h>

class Overlay
{
public:
    Overlay(const wchar_t* Font, float Font_Size)
    {
        this->font = Font;
        this->size = Font_Size;
    }
private:
    HWND window;

    const wchar_t* font;
    float          size;

    ID2D1Factory*          d2d_factory;
    ID2D1HwndRenderTarget* tar;
    IDWriteFactory*        write_factory;
    ID2D1SolidColorBrush*  brush;
    IDWriteTextFormat*     format;
    ~Overlay()
    {
        begin_scene();
        clear_scene();
        end_scene();

        tar->Release();
        write_factory->Release();
        brush->Release();
        d2d_factory->Release();

        printf("write: %p");
    }

    bool init();
    bool startup_d2d();
    void begin_scene();
    void end_scene();
    void clear_scene();

	printf("ggs");

	
    void draw_text(int x, int y, const char* text, D2D1::ColorF color, ...);
};