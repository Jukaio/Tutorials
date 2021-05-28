// application.h

#ifndef INCLUDED_APPLICATION_H
#define INCLUDED_APPLICATION_H

#include <SDL.h>
#include <SDL_image.h>

enum ApplicationStatus
{
    APPLICATION_STATUS_INITILISATION,
    APPLICATION_STATUS_RUNNING,
    APPLICATION_STATUS_TERMINATION
};



struct Application_Sprite
{
    SDL_Texture* texture;
    SDL_Rect source;
};

Application_Sprite ApplicationSpriteCreate(SDL_Texture* texture);

void ApplicationClearAndDrawBackground(SDL_Color color);
void ApplicationDrawColouredRect(SDL_FRect* rect, SDL_Color color);
void ApplicationInitialisation();
bool ApplicationShouldRun();
bool ApplicationIsRunning();
void ApplicationStop();
void ApplicationProcessEvents();
void ApplicationRun();
void ApplicationTermination();

#endif // !INCLUDED_APPLICATION_H
