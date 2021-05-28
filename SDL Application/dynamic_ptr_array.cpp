
#include "dynamic_ptr_array.h"
#include <SDL_stdinc.h>

struct DynamicPtrArray
{
    void** data;
    int count;
    int capacity;
};

DynamicPtrArray* DynamicPtrArrayCreate(int count)
{
    if(!(count > 0)) {
        return nullptr;
    }
    DynamicPtrArray* arr = (DynamicPtrArray*) SDL_malloc(sizeof(DynamicPtrArray));
    arr->data = (void**)SDL_calloc(count, sizeof(void*));
    arr->count = 0;
    arr->capacity = count;
    return arr;
}
void DynamicPtrArrayResize(DynamicPtrArray* arr, int capacity)
{
    if(arr == nullptr) {
        return;
    }
    if(!(capacity > arr->capacity)) {
        return; // Do not even bother resizing
    }

    if(arr->capacity > 0) { 
        void** temp = arr->data;
        arr->data = (void**)SDL_calloc(capacity, sizeof(void*));
        for(int i = 0; i < arr->capacity; i++) {
            arr->data[i] = temp[i];
        }
        arr->capacity = capacity;
        SDL_free(temp);
    }
}
void* DynamicPtrArrayGet(DynamicPtrArray* arr, int index)
{
    if(arr == nullptr) {
        return nullptr;
    }
    if(index > arr->count || index < 0) {
        return nullptr;
    }
    return arr->data[index];
}
void DynamicPtrArrayAdd(DynamicPtrArray* arr, void* data)
{
    if(arr == nullptr) {
        return;
    }
    if(arr->count >= arr->capacity) {
        DynamicPtrArrayResize(arr, arr->capacity * 2);
    }
    arr->data[arr->count] = data;
    arr->count += 1;
}
void DynamicPtrArrayInsert(DynamicPtrArray* arr, int index, void* data)
{
    if(arr == nullptr) {
        return;
    }
    if(index > arr->count || index < 0) {
        return;
    }
    if(arr->count >= arr->capacity) {
        DynamicPtrArrayResize(arr, arr->capacity * 2);
    }
    for(int i = arr->count - 1; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = data;
    arr->count += 1;
}
void* DynamicPtrArrayRemove(DynamicPtrArray* arr, int index)
{
    if(arr == nullptr) {
        return nullptr;
    }
    if(index >= arr->count || index < 0) {
        return nullptr;
    }
    void* removed = arr->data[index];
    for(int i = index; i < arr->count - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->count -= 1;
    return removed;
}
int DynamicPtrArrayCount(DynamicPtrArray* arr)
{
    if(arr == nullptr) {
        return -1;
    }
    return arr->count;
}
void DynamicPtrArrayDestroy(DynamicPtrArray** arr)
{
    if((*arr) == nullptr) {
        return;
    }
    if((*arr)->data == nullptr) {
        SDL_free(arr);
        return;
    }

    SDL_free((*arr)->data);
    SDL_free(*arr);
    *arr = nullptr;
}
