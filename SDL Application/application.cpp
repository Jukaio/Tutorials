
#include "application.h"
#include "texture_manager.h"
// Application Data
ApplicationStatus status{ APPLICATION_STATUS_INITILISATION };
SDL_Window* window{ nullptr };
SDL_Renderer* renderer{ nullptr };

Application_Sprite sprite{ nullptr, { 0, 0, 0, 0 } };
SDL_FRect destination;

struct NamedTexture
{
    SDL_Texture* texture;
    char* name;
};

Application_Sprite ApplicationSpriteCreate(SDL_Texture* texture)
{
    Application_Sprite to_return;
    to_return.source.x = 0;
    to_return.source.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &sprite.source.w, &sprite.source.h);
    to_return.texture = texture;
    return to_return;
}

void ApplicationClearAndDrawBackground(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void ApplicationDrawColouredRect(SDL_FRect* rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRectF(renderer, rect);
}

void ApplicationInitialisation()
{
    //textures = DynamicPtrArrayCreate(2);

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window = SDL_CreateWindow("SDL Application",/* Title */
                              50, 50,           /* Position */
                              640, 480,         /* Size */
                              0);               /* Flags */

    renderer = SDL_CreateRenderer(window, -1, 0);

    ManagerTextureInit(1);


    sprite.texture = ManagerTextureLoad("shipPink_manned.png");
    sprite.source.x = 0;
    sprite.source.y = 0;
    SDL_QueryTexture(sprite.texture, nullptr, nullptr, &sprite.source.w, &sprite.source.h);
    destination.x = 0.0f;
    destination.y = 0.0f;
    destination.w = (float) sprite.source.w;
    destination.h = (float) sprite.source.h;
}

bool ApplicationShouldRun()
{
    bool is_window_valid = window != nullptr;
    bool is_renderer_valid = renderer != nullptr;
    status = ApplicationStatus::APPLICATION_STATUS_RUNNING;
    return is_window_valid && is_renderer_valid;
}

bool ApplicationIsRunning()
{
    return status == ApplicationStatus::APPLICATION_STATUS_RUNNING;
}

void ApplicationStop()
{
    status = ApplicationStatus::APPLICATION_STATUS_TERMINATION;
}

void ApplicationProcessEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            ApplicationStop();
        }

        // TODO: Add further events later
    }
}

void ApplicationRun()
{
    ApplicationProcessEvents();

    ApplicationClearAndDrawBackground({ 255, 255, 255, 255 });
    SDL_RenderCopyF(renderer, sprite.texture, &sprite.source, &destination);

    SDL_RenderPresent(renderer);
}

void ApplicationTermination()
{
    ManagerTextureQuit();
    if(renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if(window != nullptr) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}
