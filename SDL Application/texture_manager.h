// texture_manager.h

#ifndef INCLUDED_TEXTURE_MANAGER_H
#define INCLUDED_TEXTURE_MANAGER_H

struct SDL_Texture;
struct SDL_Renderer;

void ManagerTextureInit(int capacity);
SDL_Texture* ManagerTextureLoad(const char* path);
void ManagerTextureUnload(const char* path);
void ManagerTextureQuit();

#endif // !INCLUDED_TEXTURE_MANAGER_H
