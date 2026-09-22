#define SHU_IMPLEMENTATION
#define SHUTIL_ARRAY
#include "../shutil.h"

#define INITIAL_CAPACITY 128

typedef struct my_type
{
    usz uit;
    double dbl;
    void *ptr;
} my_type;

void printArray(SHUArray array)
{
    printf("\n[ ");
    usz size = SHUArray_GetCount(array);

    for (usz i = 0; i < size; i++)
    {
        const my_type *item = SHUArray_Get(array, i);
        printf("%zu-%f-%p", item->uit, item->dbl, item->ptr);

        if (i != size - 1)
        {
            printf(", ");
        }
    }

    printf(" ]\n");
}

int main(int argc, char **argv)
{
    SHUArray array;
    SHUArray_Create(&array, sizeof(my_type), INITIAL_CAPACITY);
    printArray(array);

    my_type data0[] = {{0, 0.0, NULL}};
    SHUArray_Push(&array, data0);
    printArray(array);

    my_type data1[] = {{1, 1.1, (void *)1}, {2, 2.2, (void *)2222}};
    SHUArray_InsertRange(&array, 0, sizeof(data1) / sizeof(my_type), data1, false);

    return 0;
}