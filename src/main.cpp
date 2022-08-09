#include "SandWorld.h"

SDL_Renderer* renderer;
SDL_Window* window;

SandWorld *world = new SandWorld();

void InitSDL(const char *title, int xpos, int ypos, int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL subsystems initialised successfully" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
        if(window)
            std::cout << "Window initialised successfully" << std::endl;
        else
            std::cout << "Window failed to initialise successfully. Error code: " << SDL_GetError() << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if(renderer)
            std::cout << "Renderer initialised successfully" << std::endl;
        else
            std::cout << "Renderer failed to initialise successfully. Error code: " << SDL_GetError() << std::endl;
    }
    else{
        std::cout << "SDL subsystems failed to initialise properly. Error code: " << SDL_GetError() << std::endl;
    }
}

int main(int argc, char* args[] ) {
    InitSDL("Falling Sand! ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640);
    std::cout << "Press Q for WATER, W for sand and E for SOLID" << std::endl << std::endl;

    while(world->running){
        world->HandleEvents();
        world->DrawMatrix();
        SDL_Delay(50);
        world->Step();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
