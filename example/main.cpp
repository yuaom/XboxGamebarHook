#include "../src/gbh.h"
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

void render() {}

int main()
{
    hook* overlay = new Overlay(L"Fortnite-Win64-Shipping");

    if (!overlay->init())
        return 1;
    if (!overlay->startup_d2d())
        return 1;

    printf("hooked\n");
    for (auto start = std::chrono::steady_clock::now(), now = start; now < start + std::chrono::seconds {10}; now = std::chrono::steady_clock::now())
    {
        overlay->begin_scene();
              overlay->draw_text(10, 10, "github.com/dysprsm", D2D1::ColorF(D2D1::ColorF::Black));
        overlay->clear_scene();
        overlay->end_scene();
    }

    printf("yo\n");

    delete overlay;

    return 0;
}
