#include "../src/gbh.h"
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

void render() {}

int main()
{
    hook* overlay = new hook::procces(L"Fortnite-Win64-Shipping");

    if (!hijack->init())
        return 1;
    if (!hijack->startup_d2d())
        return 1;

    printf("hooked\n");
    for (auto start = std::chrono::steady_clock::now(), now = start; now < start + std::chrono::seconds {10}; now = std::chrono::steady_clock::now())
    {
        hijack->begin_scene();
              hijack->draw_text(10, 10, "github.com/dysprsm", D2D1::ColorF(D2D1::ColorF::Black));
        hijack->clear_scene();
        hijack->end_scene();
    }

    printf("yo\n");

    delete hook;

    return 0;
}
