
#include "texture_manager.h"
#include "dynamic_ptr_array.h"
#include <SDL_image.h>

struct NamedTexture
{
    SDL_Texture* texture;
    char* name;
};

extern SDL_Renderer* renderer; // If we don't define a renderer, we can't use texture_manger.cpp
static DynamicPtrArray* textures{ nullptr }; // Unsure how that works, if bugs delete "static"!

NamedTexture* NamedTextureCreate(const char* path)
{
    // load image
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if(!texture) {
        return nullptr;
    }
    // Allocate named texture
    NamedTexture* named_texture = (NamedTexture*) SDL_malloc(sizeof(NamedTexture));
    named_texture->texture = texture;

    // Copy c-string
    int size = SDL_strlen(path);
    named_texture->name = (char*) SDL_malloc(size);
    SDL_memcpy(named_texture->name, path, size);
    return named_texture;
}

void NamedTextureDestroy(NamedTexture* that)
{
    if(that != nullptr) {
        if(that->texture != nullptr) {
            SDL_DestroyTexture(that->texture);
        }
        if(that->name != nullptr) {
            SDL_free(that->name);
        }
        SDL_free(that);
    }
}

void ManagerTextureInit(int capacity)
{
    if(textures == nullptr) {
        textures = DynamicPtrArrayCreate(capacity);
    }

}

SDL_Texture* ManagerTextureExists(const char* path)
{
    for(int i = 0; i < DynamicPtrArrayCount(textures); i++) {
        NamedTexture* that = (NamedTexture*) DynamicPtrArrayGet(textures, i);
        if(!SDL_strcmp(that->name, path)) {
            return that->texture;
        }
    }
    return nullptr;
}
SDL_Texture* ManagerTextureLoad(const char* path)
{
    {   // If the texture already exists, just return it
        SDL_Texture* that = ManagerTextureExists(path);
        if(that) {
            return that;
        }
    }

    NamedTexture* that = NamedTextureCreate(path);
    if(that != nullptr) {
        DynamicPtrArrayAdd(textures, that);
        return that->texture;
    }
    return nullptr;
}
void ManagerTextureUnload(const char* path)
{
    for(int i = 0; i < DynamicPtrArrayCount(textures); i++) {
        NamedTexture* that = (NamedTexture*) DynamicPtrArrayGet(textures, i);
        if(!SDL_strcmp(that->name, path)) {
            DynamicPtrArrayRemove(textures, i);
            NamedTextureDestroy(that);
            return;
        }
    }
}

void ManagerTextureQuit()
{
    if(textures == nullptr) {
        return;
    }

    while(void* ptr = DynamicPtrArrayRemove(textures, 0)) {
        NamedTexture* that = (NamedTexture*) ptr;
        NamedTextureDestroy(that);
    }
    DynamicPtrArrayDestroy(&textures);
}