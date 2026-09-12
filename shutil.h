// SHUTIL_ALL : enables everything in the library

// SHUTIL_ARRAY : enables dynamic array data structure
// SHUTIL_LIST : enables linked array data structure
// SHUTIL_STACK : enables stack data structure
// SHUTIL_QUEUE : enables queue data structure
// SHUTIL_DEQUE : enables double ended queue data structure
// SHUTIL_MAP : enables hash map data structure
// SHUTIL_SET : enables hash set data structure
// SHUTIL_TREE : enables tree data structure
// SHUTIL_GRAPH : enables graph data structure

// todo algorithms

#pragma once

#ifndef SHU_HEADER
#ifdef SHU
#include SHU
#else
#include "../shu/shu.h"
#endif
#endif

#pragma region Macros

#ifdef SHUTIL_ALL
#define SHUTIL_ARRAY
#define SHUTIL_LIST
#define SHUTIL_STACK
#define SHUTIL_QUEUE
#define SHUTIL_DEQUE
#define SHUTIL_MAP
#define SHUTIL_SET
#define SHUTIL_TREE
#define SHUTIL_GRAPH
#endif

#pragma endregion Macros

#pragma region Declarations

#ifdef SHUTIL_ARRAY

// todo add results

typedef struct SHUI_Array *SHUArray;

/// @brief Creator function for SHUArray.
/// @param retList Pointer to the SHUArray to initialize.
/// @param sizeOfItem Size of the item type to store in.
/// @param initialCapacity How many items can hold in this SHUArray. Can be resized later on.
/// @return RJ_OK on success, or RJ_ERROR_ALLOCATION if internal allocation fails.
SHUResult SHUArray_Create(SHUArray retArray, usz sizeOfItem, usz initialCapacity);

/// @brief Destroyer function for SHUArray.
/// @param array SHUArray to destroy.
void SHUArray_Destroy(SHUArray array);

/// @brief Resize function for SHUArray. Can enlarge or trunc the SHUArray.
/// @param array SHUArray to resize.
/// @param newCapacity Capacity to increase or decrease.
SHUResult SHUArray_Resize(SHUArray array, usz newCapacity);

/// @brief Getter function for SHUArray. Should be cast before using. ['(<TYPE>*)Getter(...)' will give you the pointer of the stored data. You can dereference it as you want]
/// @param array Pointer to the SHUArray to get item from.
/// @param index Index to get item.
/// @return Pointer to the item at the given index.
SHUResult *SHUArray_Get(SHUArray array, usz index);

/// @brief Adder function for SHUArray. Copies {sizeOfItem} amount of data from parameter {item} to the end of the array. Uses memcpy.
/// @param array SHUArray to push item.
/// @param item Item to push to SHUArray.
/// @return The address of the added item
void *SHUArray_Push(SHUArray array, const void *item);

/// @brief Adds a range of items to the SHUArray. Uses memcpy to copy the items to the last index.
/// @param array SHUArray to push items to.
/// @param item Pointer to the first item to push.
/// @param itemCount Number of items to push.
/// @return The address of the first added item.
void *SHUArray_PushRange(SHUArray array, const void *item, usz itemCount);

/// @brief Adds an item at a specific index in the SHUArray.
/// @param array Pointer to the SHUArray to push item to.
/// @param index Index to push item at.
/// @param item Pointer to the item to push.
/// @return The address of the added item.
void *SHUArray_Insert(SHUArray array, usz index, const void *item);

/// @brief Remover function using index for SHUArray. Removes the item at the given index. Uses memmove to shift all indices of items by -1 after the removed index.
/// @param array SHUArray to remove item from.
/// @param index Index to remove item at.
void SHUArray_Pop(SHUArray array, usz index);

/// @brief Remover function using index for ListArray. Removes the item at the given index. Uses memmove to shift all indices of items by -1 after the removed index.
/// @param list ListArray to remove item from.
/// @param index Index to remove item at.
void ListArray_Remove(SHUArray array, usz index);

/// @brief Remover function using range for ListArray. Removes items from starting index. Uses memmove to shift all indices of items by item count after the removed index.
/// @param list ListArray to remove item from.
/// @param index Index to start remove item at.
/// @param itemCount Item count to remove.
void ListArray_RemoveRange(SHUArray array, usz index, usz itemCount);

/// @brief Clear function for SHUArray. Sets all the data unusable and size to 0. Capacity remains the same.
/// @param array SHUArray to clear.
void SHUArray_Clear(SHUArray array);

#endif

#ifdef SHUTIL_LIST

#endif

#ifdef SHUTIL_STACK

#endif

#ifdef SHUTIL_QUEUE

#endif

#ifdef SHUTIL_DEQUE

#endif

#ifdef SHUTIL_MAP

#endif

#ifdef SHUTIL_SET

#endif

#ifdef SHUTIL_TREE

#endif

#ifdef SHUTIL_GRAPH

#endif

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

#ifdef SHUTIL_ARRAY

SHUResult SHUArray_Create(SHUArray retArray, usz sizeOfItem, usz initialCapacity)
{
}

void SHUArray_Destroy(SHUArray array)
{
}

SHUResult SHUArray_Resize(SHUArray array, usz newCapacity)
{
}

SHUResult *SHUArray_Get(SHUArray array, usz index)
{
}

void *SHUArray_Push(SHUArray array, const void *item)
{
}

void *SHUArray_PushRange(SHUArray array, const void *item, usz itemCount)
{
}

void *SHUArray_Insert(SHUArray array, usz index, const void *item)
{
}

void SHUArray_Pop(SHUArray array, usz index)
{
}

void ListArray_Remove(SHUArray array, usz index)
{
}

void ListArray_RemoveRange(SHUArray array, usz index, usz itemCount)
{
}

void SHUArray_Clear(SHUArray array)
{
}

#endif

#ifdef SHUTIL_LIST

#endif

#ifdef SHUTIL_STACK

#endif

#ifdef SHUTIL_QUEUE

#endif

#ifdef SHUTIL_DEQUE

#endif

#ifdef SHUTIL_MAP

#endif

#ifdef SHUTIL_SET

#endif

#ifdef SHUTIL_TREE

#endif

#ifdef SHUTIL_GRAPH

#endif

#endif

#pragma endregion Definitions
