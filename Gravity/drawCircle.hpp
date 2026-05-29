#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include "structs.hpp"

void DRAW_CIRCLE(SDL_Renderer * renderer, Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int Theta = 1; Theta <= 360; Theta++) {
        double px = rect.x + rect.r * cos(Theta);
        double py = rect.y + rect.r * sin(Theta);
        SDL_RenderDrawPoint(renderer, (int)px, (int)py);
    }
}