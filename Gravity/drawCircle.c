#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

void DRAW_CIRCLE(SDL_Renderer * renderer, int x, int y, uint8_t r) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int Theta = 1; Theta <= 360; Theta++) {
        double px = x + r * cos(Theta);
        double py = y + r * sin(Theta);
        SDL_RenderDrawPoint(renderer, (int)px, (int)py);
    }
}