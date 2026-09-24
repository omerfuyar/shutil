// SHUTIL_ALL : enables everything in the library

// SHUTIL_ARRAY : enables dynamic array data structure
//             _EXPAND <multiplier> : array expands itself by <multiplier> when it is full, default to 2.0
//             _SHRINK <fraction> : array shrinks itself to <count * SHUTIL_ARRAY_EXPAND> when only <fraction> of items left in it, default to 0.25
// SHUTIL_LIST : enables doubly linked list data structure
// SHUTIL_STACK : enables stack data structure
// SHUTIL_QUEUE : enables queue data structure
// SHUTIL_DEQUE : enables double ended queue data structure
// SHUTIL_MAP : enables hash map data structure
// SHUTIL_SET : enables hash set data structure
// SHUTIL_TREE : enables tree data structure
// SHUTIL_GRAPH : enables graph data structure

// todo algorithms, allocator options for ds, 0 size assertions, maybe swap for range functions too

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

#pragma region Allocators

/// @brief The interface needed for memory management.
typedef struct SHUAllocator
{
    void *data;                                                                                         // context of the allocator, like SHUArena pointer.
    SHUResult (*Allocate)(void *allocator, SHUSlice *retMemory, usz size);                              // Returns SHUResult_ErrAllocation if allocation fails.
    SHUResult (*Reallocate)(void *allocator, SHUSliceView oldMemory, SHUSlice *retMemory, usz newSize); // Returns SHUResult_ErrAllocation if allocation fails.
    void (*Free)(void *allocator, SHUSlice *retMemory);
} SHUAllocator;

/// @brief Allocator for a given specific allocator/type.
#define SHUAllocatorGet(allocator) _Generic((allocator),                                                                                  \
    SHUArena: (SHUAllocator){.Allocate = SHUArena_Allocate, .Reallocate = SHUArena_Reallocate, .Free = SHUArena_Free, .data = allocator}, \
    SHUPool: (SHUAllocator){.Allocate = SHUPool_Allocate, .Reallocate = SHUPool_Reallocate, .Free = SHUPool_Free, .data = allocator},     \
    default: (SHUAllocator){.Allocate = SHUDefault_Allocate, .Reallocate = SHUDefault_Reallocate, .Free = SHUDefault_Free, .data = NULL})
// todo rename

#pragma region SHUDefault

SHUResult SHUDefault_Allocate(void *allocator, SHUSlice *retMemory, usz size);

SHUResult SHUDefault_Reallocate(void *allocator, SHUSlice oldMemory, SHUSlice *retMemory, usz newSize);

void SHUDefault_Free(void *allocator, SHUSlice *retMemory);

#pragma endregion SHUDefault

#pragma region SHUArena

typedef struct SHUI_Arena *SHUArena;

SHUResult SHUArena_Create(SHUArena *retAllocator, usz capacity);

void SHUArena_Destroy(SHUArena *allocator);

SHUResult SHUArena_Allocate(void *allocator, SHUSlice *retMemory, usz size);

SHUResult SHUArena_Reallocate(void *allocator, SHUSliceView oldMemory, SHUSlice *retMemory, usz newSize);

void SHUArena_Free(void *allocator, SHUSlice *retMemory);

#pragma endregion SHUArena

#pragma region SHUPool

typedef struct SHUI_Pool *SHUPool;

SHUResult SHUPool_Create(SHUPool *retAllocator, usz blockSize, usz blokCapacity);

void SHUPool_Destroy(SHUPool *allocator);

SHUResult SHUPool_Allocate(void *allocator, SHUSlice *retMemory, usz size);

SHUResult SHUPool_Reallocate(void *allocator, SHUSliceView oldMemory, SHUSlice *retMemory, usz newSize);

void SHUPool_Free(void *allocator, SHUSlice *retMemory);

#pragma endregion SHUPool

#pragma endregion Allocators

#pragma region Data Structures

#ifdef SHUTIL_ARRAY

#ifndef SHUTIL_ARRAY_EXPAND
#define SHUTIL_ARRAY_EXPAND 2.0
#endif

#ifndef SHUTIL_ARRAY_SHRINK
#define SHUTIL_ARRAY_SHRINK 0.25
#endif

/// @brief Handle of a shutil array.
typedef struct SHUI_Array *SHUArray;

/// @brief Create a SHUArray.
/// @param retArray Address of the array buffer.
/// @param sizeOfItem Size of the item type to store in.
/// @param initialCapacity How many items can hold in this SHUArray. Can be resized later on.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Create(SHUArray *retArray, usz sizeOfItem, usz initialCapacity);

/// @brief Destroys a SHUArray.
/// @param array SHUArray to destroy.
void SHUArray_Destroy(SHUArray *array);

/// @brief Returns the current capacity of the array.
/// @param array SHUArray to get capacity.
/// @return The capacity of the array.
usz SHUArray_GetCapacity(SHUArray array);

/// @brief Returns the current item count of the array.
/// @param array SHUArray to get item count.
/// @return The item count of the array.
usz SHUArray_GetCount(SHUArray array);

/// @brief Returns the current item size of the array.
/// @param array SHUArray to get item size.
/// @return The item size of the array.
usz SHUArray_GetItemSize(SHUArray array);

/// @brief Resize function for SHUArray. Can enlarge or trunc the SHUArray.
/// @param retArray Pointer to the SHUArray to resize.
/// @param newCapacity Capacity to increase or decrease.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
/// @note Removes the elements if newCapacity is smaller than current count
SHUResult SHUArray_Resize(SHUArray *retArray, usz newCapacity);

/// @brief Index an item inside SHUArray.
/// @param array SHUArray to get item from.
/// @param index Index to get item.
/// @return Pointer to the item at the given index. Do not write to returned address, use `SHUArray_Set` instead.
const void *SHUArray_Get(SHUArray array, usz index);

/// @brief Change an item inside SHUArray.
/// @param array SHUArray to set item in.
/// @param index Index to set item.
void SHUArray_Set(SHUArray array, usz index, const void *item);

/// @brief Adds an item to the end of the SHUArray.
/// @param array Pointer to the SHUArray to push item.
/// @param item Item to push to SHUArray.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Push(SHUArray *array, const void *item);

/// @brief Adds a range of items to the and of the SHUArray.
/// @param array Pointer to the SHUArray to push items to.
/// @param itemCount Number of items to push.
/// @param items Pointer to the first item to push.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_PushRange(SHUArray *array, usz itemCount, const void *items);

/// @brief Adds an item at a specific index in the SHUArray. Shifting the tail part.
/// @param array Pointer to the SHUArray to insert item to.
/// @param index Index to insert item at.
/// @param item Pointer to the item to insert.
/// @param swap Puts the indexed items to tail if true, shifts all the latter items otherwise.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Insert(SHUArray *array, usz index, const void *item, bool swap);

/// @brief Adds a range of items at a specific index in the SHUArray. Shifting the tail part.
/// @param array Pointer to the SHUArray to insert item to.
/// @param index Index to insert item at.
/// @param itemCount Number of items to insert.
/// @param items Pointer to the first item to insert.
/// @param swap Puts the indexed items to tail if true, shifts all the latter items otherwise.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_InsertRange(SHUArray *array, usz index, usz itemCount, const void *items, bool swap);

/// @brief Removes the last item in the array.
/// @param array Pointer to the SHUArray to pop item from.
/// @param retItem Buffer to write the popped item. Leave NULL if not needed.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Pop(SHUArray *array, void *retItem);

/// @brief Removes a range of items from end of the array.
/// @param array Pointer to the SHUArray to pop items from.
/// @param retItem Buffer to write popped items. Leave NULL if not needed.
/// @param itemCount Item count to remove.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_PopRange(SHUArray *array, usz itemCount, void *retItems);

/// @brief Removes the item at the given index.
/// @param array Pointer to the SHUArray to remove item from.
/// @param index Index to remove item at.
/// @param retItem Buffer to write the removed item. Leave NULL if not needed.
/// @param swap Puts the tail item to index if true, shifts all the latter items otherwise.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Remove(SHUArray *array, usz index, void *retItem, bool swap);

/// @brief Removes a range of items from starting index.
/// @param array Pointer to the SHUArray to remove items from.
/// @param index Index to start removing items from.
/// @param itemCount Item count to remove.
/// @param retItem Buffer to write removed items. Leave NULL if not needed.
/// @param swap Puts the tail items to index if true, shifts all the latter items otherwise.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_RemoveRange(SHUArray *array, usz index, usz itemCount, void *retItems, bool swap);

/// @brief Empties the array and resizes it.
/// @param array Array address to clear.
/// @param newCapacity New capacity of the array.
/// @return SHUResult_Ok on success, or SHUResult_ErrAllocation if internal allocation fails.
SHUResult SHUArray_Clear(SHUArray *array, usz newCapacity);

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

#pragma endregion Data Structures

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

#pragma region Allocators

#pragma region SHUDefault

SHUResult SHUDefault_Allocate(void *allocator, SHUSlice *retMemory, usz size)
{
    (void)allocator;

    retMemory->data = malloc(size);
    if (retMemory->data == NULL)
    {
        retMemory->size = 0;
        return SHUResult_ErrAllocation;
    }

    retMemory->size = size;
    return SHUResult_Ok;
}

SHUResult SHUDefault_Reallocate(void *allocator, SHUSlice oldMemory, SHUSlice *retMemory, usz newSize)
{
    (void)allocator;

    retMemory->data = realloc(oldMemory.data, newSize);
    if (retMemory->data == NULL)
    {
        retMemory->size = 0;
        return SHUResult_ErrAllocation;
    }

    retMemory->size = newSize;
    return SHUResult_Ok;
}

void SHUDefault_Free(void *allocator, SHUSlice *retMemory)
{
    (void)allocator;

    if (retMemory == NULL || retMemory->data == NULL)
    {
        return;
    }

    free(retMemory->data);
    retMemory->data = NULL;
    retMemory->size = 0;
}

#pragma endregion SHUDefault

#pragma region SHUArena

typedef struct SHUI_ArenaChunk
{
    struct SHUI_ArenaChunk *next;
    usz count;
    // memory
} SHUI_ArenaChunk;

typedef struct SHUI_Arena
{
    SHUI_ArenaChunk *chunkHead;
    usz chunkCapacity; // in bytes
} SHUI_Arena;

SHUResult SHUArena_Create(SHUArena *retAllocator, usz capacity)
{
    (void)capacity;
    (void)retAllocator;
    return SHUResult_Ok;
}

void SHUArena_Destroy(SHUArena *allocator)
{
    (void)allocator;
}

SHUResult SHUArena_Allocate(void *allocator, SHUSlice *retMemory, usz size)
{
    (void)allocator;
    (void)retMemory;
    (void)size;
    return SHUResult_Ok;
}

SHUResult SHUArena_Reallocate(void *allocator, SHUSliceView oldMemory, SHUSlice *retMemory, usz newSize)
{
    (void)allocator;
    (void)oldMemory;
    (void)retMemory;
    (void)newSize;
    return SHUResult_Ok;
}

void SHUArena_Free(void *allocator, SHUSlice *retMemory)
{
    (void)allocator;
    (void)retMemory;
}

#pragma endregion SHUArena

#pragma region SHUPool

// todo every allocated memory starts after header

typedef struct SHUI_AllocatorPoolNode
{
    struct SHUI_AllocatorPoolNode *next;
    // node memory
} SHUI_AllocatorPoolNode;

typedef struct SHUI_PoolChunk
{
    struct SHUI_PoolChunk *next;
    // chunk memory
} SHUI_PoolChunk;

typedef struct SHUI_Pool
{
    struct SHUI_PoolChunk *chunkHead;
    SHUI_AllocatorPoolNode *freeHead;
    usz blockSize;
    usz chunkNodeCapacity;
} SHUI_Pool;

SHUResult SHUPool_Create(SHUPool *retAllocator, usz blockSize, usz blokCapacity)
{
    (void)retAllocator;
    (void)blockSize;
    (void)blokCapacity;
    return SHUResult_Ok;
}

void SHUPool_Destroy(SHUPool *allocator)
{
    (void)allocator;
}

SHUResult SHUPool_Allocate(void *allocator, SHUSlice *retMemory, usz size)
{
    (void)allocator;
    (void)retMemory;
    (void)size;
    return SHUResult_Ok;
}

SHUResult SHUPool_Reallocate(void *allocator, SHUSliceView oldMemory, SHUSlice *retMemory, usz newSize)
{
    (void)allocator;
    (void)oldMemory;
    (void)retMemory;
    (void)newSize;
    return SHUResult_Ok;
}

void SHUPool_Free(void *allocator, SHUSlice *retMemory)
{
    (void)allocator;
    (void)retMemory;
}

#pragma endregion SHUPool

#pragma endregion Allocators

#pragma region Data Structures

#ifdef SHUTIL_ARRAY

typedef struct SHUI_Array
{
    usz capacity;
    usz count;
    usz itemSize;
    // data
} SHUI_Array;

/// !!! USE ONLY WITH `SHUArray` IN PARAMETER !!!
#define SHUI_ArrayGetItem(array, index) ((void *)((((u8 *)(array)) + sizeof(SHUI_Array)) + ((index) * (array)->itemSize)))

/// !!! USE ONLY WITH `SHUArray` IN PARAMETER !!!
#define SHUI_ArrayAssertIndex(array, index) SHU_Assert((index) < (array)->count,                                                                          \
                                                       "Index out of range : index '%zu', array.count '%zu', array.capacity '%zu', array.itemSize '%zu'", \
                                                       (index), (array)->count, (array)->capacity, (array)->itemSize)

#define SHUI_ArrayAssertRemoval(array, itemCount) SHU_Assert((array)->count >= (itemCount),                                                 \
                                                             "Cannot remove more items than existing : array.count '%zu', itemCount '%zu'", \
                                                             (array)->count, (itemCount))

#define SHUI_ArrayAssertSize(size) SHU_Assert((size) != 0, "0 value for size variable " #size)

SHUResult SHUArray_Create(SHUArray *retArray, usz sizeOfItem, usz initialCapacity)
{
    SHU_AssertNullPointer(retArray);
    SHUI_ArrayAssertSize(sizeOfItem);
    SHUI_ArrayAssertSize(initialCapacity);

    SHUArray array = (SHUArray)malloc(sizeof(SHUI_Array) + initialCapacity * sizeOfItem); //! important
    if (array == NULL)
    {
        *retArray = NULL;
        return SHUResult_ErrAllocation;
    }

    array->capacity = initialCapacity;
    array->count = 0;
    array->itemSize = sizeOfItem;

    *retArray = array;
    return SHUResult_Ok;
}

void SHUArray_Destroy(SHUArray *array)
{
    SHU_AssertNullPointer(array);

    free(*array);
    *array = NULL;
}

usz SHUArray_GetCapacity(SHUArray array)
{
    SHU_AssertNullPointer(array);

    return array->capacity;
}

usz SHUArray_GetCount(SHUArray array)
{
    SHU_AssertNullPointer(array);

    return array->count;
}

usz SHUArray_GetItemSize(SHUArray array)
{
    SHU_AssertNullPointer(array);

    return array->itemSize;
}

SHUResult SHUArray_Resize(SHUArray *retArray, usz newCapacity)
{
    SHU_AssertNullPointer(retArray);
    SHU_AssertNullPointer(*retArray);
    SHUI_ArrayAssertSize(newCapacity);

    SHUArray resized = (SHUArray)realloc(*retArray, sizeof(SHUI_Array) + newCapacity * (*retArray)->itemSize);
    if (resized == NULL)
    {
        return SHUResult_ErrAllocation;
    }

    resized->capacity = newCapacity;
    if (resized->count > newCapacity)
    {
        resized->count = newCapacity;
    }

    *retArray = resized;

    return SHUResult_Ok;
}

const void *SHUArray_Get(SHUArray array, usz index)
{
    SHU_AssertNullPointer(array);
    SHUI_ArrayAssertIndex(array, index);

    return SHUI_ArrayGetItem(array, index);
}

void SHUArray_Set(SHUArray array, usz index, const void *item)
{
    SHU_AssertNullPointer(array);
    SHU_AssertNullPointer(item);
    SHUI_ArrayAssertIndex(array, index);

    memcpy(SHUI_ArrayGetItem(array, index), item, array->itemSize);
}

SHUResult SHUArray_Push(SHUArray *array, const void *item)
{
    return SHUArray_PushRange(array, 1, item);
}

SHUResult SHUArray_PushRange(SHUArray *array, usz itemCount, const void *items)
{
    SHU_AssertNullPointer(array);

    return SHUArray_InsertRange(array, SHUArray_GetCount(*array), itemCount, items, true);
}

SHUResult SHUArray_Insert(SHUArray *array, usz index, const void *item, bool swap)
{
    return SHUArray_InsertRange(array, index, 1, item, swap);
}

SHUResult SHUArray_InsertRange(SHUArray *array, usz index, usz itemCount, const void *items, bool swap)
{
    SHU_AssertNullPointer(array);
    SHU_AssertNullPointer(*array);
    SHU_AssertNullPointer(items);
    SHUI_ArrayAssertSize(itemCount);
    if (index != (*array)->count)
    {
        SHUI_ArrayAssertIndex(*array, index);
    }

    SHUArray realArray = *array;
    usz newSize = realArray->count + itemCount;

    if (newSize > realArray->capacity) // will be full
    {
        SHU_ReturnResult(SHUArray_Resize(array, newSize * SHUTIL_ARRAY_EXPAND));
    }

    realArray = *array;

    if (swap)
    {
        usz moveCount = SHUMin(itemCount, realArray->count - index);
        memmove(SHUI_ArrayGetItem(realArray, realArray->count + itemCount - moveCount),
                SHUI_ArrayGetItem(realArray, index),
                moveCount * realArray->itemSize);
    }
    else
    {
        memmove(SHUI_ArrayGetItem(realArray, index + itemCount),
                SHUI_ArrayGetItem(realArray, index),
                (realArray->count - index) * realArray->itemSize);
    }

    memcpy(SHUI_ArrayGetItem(realArray, index), items, itemCount * realArray->itemSize);

    realArray->count += itemCount;

    return SHUResult_Ok;
}

SHUResult SHUArray_Pop(SHUArray *array, void *retItem)
{
    return SHUArray_PopRange(array, 1, retItem);
}

SHUResult SHUArray_PopRange(SHUArray *array, usz itemCount, void *retItems)
{
    SHU_AssertNullPointer(array);
    SHU_AssertNullPointer(*array);
    SHUI_ArrayAssertRemoval(*array, itemCount);

    return SHUArray_RemoveRange(array, SHUArray_GetCount(*array) - itemCount, itemCount, retItems, true);
}

SHUResult SHUArray_Remove(SHUArray *array, usz index, void *retItem, bool swap)
{

    return SHUArray_RemoveRange(array, index, 1, retItem, swap);
}

SHUResult SHUArray_RemoveRange(SHUArray *array, usz index, usz itemCount, void *retItems, bool swap)
{
    SHU_AssertNullPointer(array);
    SHUI_ArrayAssertSize(itemCount);

    SHUArray realArray = *array;
    SHU_AssertNullPointer(realArray);
    SHUI_ArrayAssertIndex(realArray, index);
    SHUI_ArrayAssertRemoval(realArray, itemCount);

    SHU_Assert(realArray->count >= (index + itemCount),
               "Removal range out of bounds :  array.count '%zu', index '%zu', itemCount '%zu'",
               realArray->count, index, itemCount);

    if (retItems != NULL)
    {
        memcpy(retItems, SHUI_ArrayGetItem(realArray, index), itemCount * realArray->itemSize);
    }

    if (swap)
    {
        usz moveCount = SHUMin(itemCount, realArray->count - index - itemCount);
        memmove(SHUI_ArrayGetItem(realArray, index),
                SHUI_ArrayGetItem(realArray, realArray->count - moveCount),
                moveCount * realArray->itemSize);
    }
    else
    {
        memmove(SHUI_ArrayGetItem(realArray, index),
                SHUI_ArrayGetItem(realArray, index + itemCount),
                (realArray->count - index - itemCount) * realArray->itemSize);
    }

    realArray->count -= itemCount;

    // todo maybe add a minimum size
    if (realArray->count != 0 && realArray->count < (usz)(realArray->capacity * SHUTIL_ARRAY_SHRINK)) // more than 3/4 empty
    {
        SHU_ReturnResult(SHUArray_Resize(array, realArray->count * SHUTIL_ARRAY_EXPAND));
    }

    return SHUResult_Ok;
}

SHUResult SHUArray_Clear(SHUArray *array, usz newCapacity)
{
    SHU_AssertNullPointer(array);
    SHU_AssertNullPointer(*array);

    (*array)->count = 0;
    return SHUArray_Resize(array, newCapacity);
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

#pragma endregion Data Structures

#endif

#pragma endregion Definitions
