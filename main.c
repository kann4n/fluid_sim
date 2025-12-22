#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define SCREEN_WIDTH 900
#define SCREEN_HIGHT 600
#define CELL_SIZE 12
#define COLs SCREEN_WIDTH / CELL_SIZE
#define ROWs SCREEN_HIGHT / CELL_SIZE

// colors
#define WHITE 0xffffff
#define BLACK 0x000000
#define BLUE 0x0000ff
#define GRAY 0x333333

void drawGrid(SDL_Surface *surface)
{
    for (int i = 0; i < COLs; i++)
    {
        SDL_Rect colRect = (SDL_Rect){i * CELL_SIZE, 0, 1, SCREEN_HIGHT};
        SDL_FillSurfaceRect(surface, &colRect, GRAY);
    }
    for (int i = 0; i < COLs; i++)
    {
        SDL_Rect rowRect = (SDL_Rect){0, i * CELL_SIZE, SCREEN_WIDTH, 1};
        SDL_FillSurfaceRect(surface, &rowRect, GRAY);
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Fluid Sim", SCREEN_WIDTH, SCREEN_HIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect){100, 100, 100, 50};
    SDL_Rect rect2 = (SDL_Rect){200, 100, 100, 50};

    uint8_t running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_EVENT_MOUSE_MOTION)
            {
                uint32_t state = event.motion.state;
                // printf("%d\n", state);
                if (state & SDL_BUTTON_LEFT)
                {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    SDL_Rect nrect = (SDL_Rect){x, y, CELL_SIZE, CELL_SIZE};
                    SDL_FillSurfaceRect(surface, &nrect, WHITE);
                }
            }
        }
        drawGrid(surface);
        SDL_FillSurfaceRect(surface, &rect, WHITE);
        SDL_FillSurfaceRect(surface, &rect2, BLUE);
        SDL_UpdateWindowSurface(window);
    }
    SDL_Delay(1000); // 1 sec wait
}