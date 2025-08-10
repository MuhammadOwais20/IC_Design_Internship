#include <verilated.h>
#include "Vvga_controller.h" 
#include <SDL2/SDL.h>

Vvga_controller* top;
vluint64_t main_time = 0;

double sc_time_stamp() { return main_time; }

uint16_t generate_pixel_data(uint16_t v) {
    if (v < 150) return 0xF800; // Red
    if (v < 300) return 0x07E0; // Green
    if (v < 450) return 0x001F; // Blue
    return 0xFFFF;              // White
}

int main() {
    Verilated::traceEverOn(true);
    top = new Vvga_controller;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("VGA Output",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGB888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             800, 600);

    uint32_t* pixels = new uint32_t[800 * 600]();
    uint16_t sram[800 * 600] = {0}; // Simulated fake SRAM

    // Reset sequence
    top->reset = 1;
    for (int i = 0; i < 5; ++i) {
        top->clk = 0; top->eval(); main_time++;
        top->clk = 1; top->eval(); main_time++;
    }
    top->reset = 0;

    
    while (!Verilated::gotFinish() && main_time < 50'000'000) {
        // Clock low
        top->clk = 0;
        top->eval();
        main_time++;

        sram[top->sram_address] = generate_pixel_data(top->vc);

        top->sram_data = sram[top->sram_address];

        top->clk = 1;
        top->eval();
        main_time++;

        if (top->video_on) {
            uint16_t sram_data = top->sram_data;
            uint8_t r = (sram_data >> 11) & 0x1F;
            uint8_t g = (sram_data >> 5)  & 0x3F;
            uint8_t b =  sram_data        & 0x1F;
            r <<= 3; g <<= 2; b <<= 3;

            if (top->hc < 800 && top->vc < 600) {
                pixels[top->vc * 800 + top->hc] = (r << 16) | (g << 8) | b;
            }
        }

        if (top->vc == 0 && top->hc == 0) {
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
