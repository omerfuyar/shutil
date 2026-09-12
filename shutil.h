// SHUTIL_ALL : enables all data structures
// SHUTIL_ARRAY : enables dynamic array data structure
// SHUTIL_LIST : enables linked list data structure
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
