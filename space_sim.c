#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

void show_debug_info(const char *msg, int debug)
{
        SDL_Log("%s", msg);
        if (debug)
                SDL_Log(" | %s", SDL_GetError());
}
struct PippetPoint
{
        float x;
        float y;
};

typedef struct
{
        char name[16]; // 2 bytes
        int mass;      // int will work since it rel mass to mercury
        float radius;
        struct PippetPoint pippetPoint; // this is the point the body will orbit around
        float distance; // distance from pippetPoint
        SDL_Texture *texture;
        SDL_FRect rect;
} Body;

int main(int argc, char *argv[])
{
        int debug = 0;

        // 2. Check for "-d" flag
        if (argc > 1)
        {
                if (strcmp(argv[1], "-d") == 0)
                {
                        SDL_Log("Debug Mode: Enabled");
                        debug = 1;
                }
        }

        if (!SDL_Init(SDL_INIT_VIDEO))
        {
                show_debug_info("SDL_Init Failed", debug);
                return -1; // -1 = init error
        }

        SDL_Window *pwindow = NULL;
        SDL_Renderer *prenderer = NULL;

        if (!SDL_CreateWindowAndRenderer("Space Sim", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &pwindow, &prenderer))
        {
                show_debug_info("Window/Renderer Failed", debug);
                return -2; // -2 = window/rend error
        }

        int running = 1;

        SDL_Texture *sunTex = IMG_LoadTexture(prenderer, "imgs/assets/sun.png");
        SDL_Texture *earthTex = IMG_LoadTexture(prenderer, "imgs/assets/earth.png");
        SDL_Texture *moonTex = IMG_LoadTexture(prenderer, "imgs/assets/moon.jpg");

        if (!sunTex || !earthTex || !moonTex)
        {
                show_debug_info("Failed to Load Textures", debug);
                SDL_DestroyRenderer(prenderer);
                SDL_DestroyWindow(pwindow);
                return -3; // -3 = texture load error
        }

        float sunSize = 100;
        float centerX = SCREEN_WIDTH / 2;
        float centerY = SCREEN_HEIGHT / 2;

        SDL_FRect sunRect = {centerX - sunSize / 2, centerY - sunSize / 2, sunSize, sunSize};

        Body earth = {
            .name = "Earth",
            .mass = 18,
            .radius = 25,
            .pippetPoint = {centerX, centerY},
            .distance = 200,
            .texture = earthTex,
            .rect = {600, 300, 50, 50},
        };
        Body moon = {
            .name = "Moon",
            .mass = 1,
            .radius = 10,
            .pippetPoint = {earth.rect.x + earth.radius, earth.rect.y + earth.radius},
            .distance = 60,
            .texture = moonTex,
            .rect = {650, 300, 20, 20},
        };

        float time = 0;
        float moontimeScale = 1.1;
        while (running)
        {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                        if (event.type == SDL_EVENT_QUIT)
                                running = 0;
                }

                SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255); // black bg
                SDL_RenderClear(prenderer);                      // clear with black

                // sun
                SDL_RenderTexture(prenderer, sunTex, NULL, &sunRect);
                // earth
                SDL_RenderTexture(prenderer, earthTex, NULL, &earth.rect);
                // moon
                SDL_RenderTexture(prenderer, moonTex, NULL, &moon.rect);
                // earth rotate anim by math sin and cos
                // curr this is fake need to study phy and math more to make it more real
                // to use
                //      Fgi = G * m1 * m2 / r^2
                //      Fei = K * q1 * q2 / r^2
                //      Fi = Fgi + Fei for i th planet by for loop idk
                // todo
                //      make more animation and add more planets
                //      make orbit hints and fix time scale
                //      use real values
                //      add satalaites and sound and muisc
                //      add randome twists like comets and meteors alins and god kannan cameo idk but why 
                earth.rect.y = earth.pippetPoint.y + earth.distance * cos(time);
                earth.rect.x = earth.pippetPoint.x + earth.distance * sin(time);

                moon.rect.y = moon.pippetPoint.y + moon.distance * cos(time*moontimeScale);
                moon.rect.x = moon.pippetPoint.x + moon.distance * sin(time*moontimeScale);

                time += 0.01;
                moon.pippetPoint.x = earth.rect.x + earth.radius;
                moon.pippetPoint.y = earth.rect.y + earth.radius;

                SDL_RenderPresent(prenderer);
                SDL_Delay(16);
        }

        // Distroy
        SDL_Log("Program Terminated");
        SDL_DestroyTexture(sunTex);
        SDL_DestroyTexture(earthTex);
        SDL_DestroyRenderer(prenderer);
        SDL_DestroyWindow(pwindow);
        SDL_Quit();
        return 0;
}