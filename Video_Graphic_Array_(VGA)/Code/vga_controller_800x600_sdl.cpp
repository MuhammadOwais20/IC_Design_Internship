#include <verilated.h>
#include "Vvga_controller_800x600.h"
#include <SDL2/SDL.h>

vluint64_t main_time = 0;
double sc_time_stamp() { return main_time; }

Vvga_controller_800x600* top;

uint16_t generate_pixel_data(uint16_t v) {
    if (v < 150) return 0xF800; // Red
    if (v < 300) return 0x07E0; // Green
    if (v < 450) return 0x001F; // Blue
    return 0xFFFF;              // White
}

int main() {
    int argc = 1;
    const char* argv[] = {"tb_vga_sdl"};
    Verilated::commandArgs(argc, argv);

    top = new Vvga_controller_800x600;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("VGA Output", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
    uint32_t* pixels = new uint32_t[800 * 600]();

    top->reset = 1;
    for (int i = 0; i < 5; ++i) {
        top->clk = 0; top->eval(); main_time++;
        top->clk = 1; top->eval(); main_time++;
    }
    top->reset = 0;

    while (!Verilated::gotFinish() && main_time < 20'000'000) {
        top->clk = 0; top->eval(); main_time++;
        top->clk = 1; top->eval(); main_time++;

        if (top->hc < 800 && top->vc < 600) {
            uint16_t sram_data = generate_pixel_data(top->vc);
            top->sram_data = sram_data;

            uint8_t r = ((sram_data >> 11) & 0x1F) << 3;
            uint8_t g = ((sram_data >> 5) & 0x3F) << 2;
            uint8_t b = (sram_data & 0x1F) << 3;

            pixels[top->vc * 800 + top->hc] = (r << 16) | (g << 8) | b;
        }

        if (top->hc == 0 && top->vc == 0) {
            SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_PollEvent(NULL);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete[] pixels;
    delete top;

    return 0;
}

