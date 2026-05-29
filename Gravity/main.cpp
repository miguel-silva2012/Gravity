#include <iostream>
#include <SDL2/SDL.h>

#include "drawCircle.hpp"
#include "structs.hpp"

#define G 6.674184

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error on start SDL!" << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Fisics Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        700, 500,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Error in create the window!");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event evento;

    Rect rect1 = {350, 250, 0, 0, 0, 0, 10, 25};

    Rect rect2 = {350, 100, .8, 0, 0, 0, 30, 10};

    bool running = true;

    while (running) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                running = false;  
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);        
        
        DRAW_CIRCLE(renderer, rect1);
        DRAW_CIRCLE(renderer, rect2);

        rect1.velx += rect1.accx;
        rect1.x += rect1.velx;

        rect1.vely += rect1.accy;
        rect1.y += rect1.vely;

        rect2.velx += rect2.accx;
        rect2.x += rect2.velx;

        rect2.vely += rect2.accy;
        rect2.y += rect2.vely;

        double d = sqrt(pow(rect2.x - rect1.x, 2) + pow(rect2.y - rect1.y, 2));

        double Fx1 = (G * rect1.mass * rect2.mass) / (d * d);

        rect2.accx = (Fx1 / rect2.mass) * (rect2.x > rect1.x ? -1 : 1);
        rect2.accy = (Fx1 / rect2.mass) * (rect2.y > rect1.y ? -1 : 1);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}