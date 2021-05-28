// DynamicPtrArray.h

#ifndef INCLUDED_DYNAMIC_PTR_ARRAY_H
#define INCLUDED_DYNAMIC_PTR_ARRAY_H

struct DynamicPtrArray;

DynamicPtrArray* DynamicPtrArrayCreate(int count);
void DynamicPtrArrayResize(DynamicPtrArray* arr, int capacity);
void* DynamicPtrArrayGet(DynamicPtrArray* arr, int index);
void DynamicPtrArrayAdd(DynamicPtrArray* arr, void* data);
void DynamicPtrArrayInsert(DynamicPtrArray* arr, int index, void* data);
void* DynamicPtrArrayRemove(DynamicPtrArray* arr, int index);
int DynamicPtrArrayCount(DynamicPtrArray* arr);
void DynamicPtrArrayDestroy(DynamicPtrArray** arr);

#endif // !INCLUDED_DYNAMIC_PTR_ARRAY_H
