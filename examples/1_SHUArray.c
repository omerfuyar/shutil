#define SHUTIL_ARRAY
#include "../shutil.h"

typedef struct my_type
{
    usz uit;
    double dbl;
    void *ptr;
} my_type;

void printArray(SHUArray array)
{
    printf("[ ");
    usz size = SHUArray_GetCount(array);

    for (usz i = 0; i < size; i++)
    {
        const my_type *item = SHUArray_Get(array, i);
        printf("%zu-%.1f-%p", item->uit, item->dbl, item->ptr);

        if (i != size - 1)
        {
            printf(", ");
        }
    }

    printf(" ]\n");
}

int main(void)
{
    // array of my_type with room for 4 items, grows by itself when full
    SHUArray array;
    SHU_AssertResult(SHUArray_Create(&array, sizeof(my_type), 4));

    // items are copied into the array
    my_type data0 = {0, 0.0, NULL};
    SHU_AssertResult(SHUArray_Push(&array, &data0));

    my_type data1[] = {{1, 1.1, (void *)0xdead}, {2, 2.2, (void *)0xbeef}};
    SHU_AssertResult(SHUArray_PushRange(&array, 2, data1));
    printArray(array); // [ 0, 1, 2 ]

    // insert shifts the tail, insert with swap moves the item at index to the end instead
    my_type data3 = {3, 3.3, NULL};
    SHU_AssertResult(SHUArray_Insert(&array, 0, &data3, false));
    printArray(array); // [ 3, 0, 1, 2 ]

    my_type data4 = {4, 4.4, NULL};
    SHU_AssertResult(SHUArray_Insert(&array, 0, &data4, true));
    printArray(array); // [ 4, 0, 1, 2, 3 ]

    // get returns a read only pointer, use set to change an item
    const my_type *item = SHUArray_Get(array, 2);
    printf("item at 2 : %zu-%.1f-%p", item->uit, item->dbl, item->ptr);

    my_type data5 = {5, 5.5, NULL};
    SHUArray_Set(array, 2, &data5);
    printArray(array); // [ 4, 0, 5, 2, 3 ]

    // remove works the same way, swap fills the hole with the last item
    my_type removed;
    SHU_AssertResult(SHUArray_Remove(&array, 0, &removed, true));
    printArray(array); // [ 3, 0, 5, 2 ]

    SHU_AssertResult(SHUArray_Pop(&array, NULL));
    printArray(array); // [ 3, 0, 5 ]

    printf("count : %zu, capacity : %zu", SHUArray_GetCount(array), SHUArray_GetCapacity(array));

    SHUArray_Destroy(&array);

    return 0;
}
