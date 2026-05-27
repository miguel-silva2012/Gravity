#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define G 6.67430e-11

struct Rect {
    double x, y;
    double velx, vely;
    double accx, accy;
    uint8_t mass;
    uint8_t h, w;
};

void DRAW_RECT(SDL_Renderer * renderer, struct Rect rrect) {
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_Rect rect;

   rect.x = (int)rrect.x;
   rect.y = (int)rrect.y;
   rect.w = rrect.w;
   rect.h = rrect.h;

   SDL_RenderFillRect(renderer, &rect);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      printf("Error on start SDL!");
      return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Simulation fisics",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 400,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Error in create the window!");
        return 1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event evento;

    bool running = true;

    struct Rect rect1 = {100, 100, 1, 0, .01, 0, 10, 25, 25};

    struct Rect rect2 = {100, 300, 1, 0, .1, 0, 20, 25, 25};

    while (running) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                running = false;  
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);        

        DRAW_RECT(renderer, rect1);
        DRAW_RECT(renderer, rect2);        

        rect1.velx += rect1.accx;
        rect1.x += rect1.velx;

        rect1.vely += rect1.accy;
        rect1.y += rect1.vely;

        rect2.velx += rect2.accx;
        rect2.x += rect2.velx;

        rect2.vely += rect2.accy;
        rect2.y += rect2.vely;

        double d1 = sqrt(pow(rect2.x - rect1.x, 2) + pow(rect2.y - rect1.y, 2));

        double force = (G * rect1.mass * rect2.mass) / (d1 * d1);

        printf("Force: %lf\n", force);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}