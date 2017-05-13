#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WIDTH 800
#define HEIGHT 600
#define BOX_SIZE 50
#define SPEED 10

SDL_Rect box;
SDL_Renderer *renderer = NULL;
int speed[2] = {SPEED, SPEED};

void loop() {
    if (box.x + box.w > WIDTH ||
        box.x < 0)
        speed[0] = - speed[0];

    if (box.y + box.h > HEIGHT ||
        box.y < 0)
        speed[1] = - speed[1];

    box.x += speed[0];
    box.y += speed[1];

    SDL_RenderFillRect(renderer, &box);
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    SDL_Window *win = NULL;

    win = SDL_CreateWindow("hello", 0, 0, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1,0);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    box = (SDL_Rect){0, 0, BOX_SIZE, BOX_SIZE};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 60, 1);
#else
    while (1) {
        loop();
    }
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    
    return 0;
}
