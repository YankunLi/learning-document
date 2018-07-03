#include <stdio.h>
#include <malloc.h>

static int get_max_k(int *array, int low, int high, int index);
static int sort(int *array, int low, int high);

int main(int argc, char *argv[])
{
    int integer_array[] = {1,0,7, 4, 6, 9};
    int array_len = sizeof(integer_array) / sizeof(integer_array[0]);
    printf("array length is %d \n", array_len);
    char n = argv[1][0];
    int kmax = get_max_k(integer_array, 0, array_len - 1, argv[1][0] - '0');
    printf("%d", kmax);
    return 0;
}

static int sort(int *array, int low, int high)
{
    if (low > high) {
        return -1;
    }
    int key = array[low];
    while (low < high) {
        while (array[high] >= key && low < high) {
            high--;
        }
        array[low] = array[high];
        while (array[low] <= key && low < high) {
            low++;
        }
        array[high] = array[low];
    }
    array[high] = key;

    return high;
}

static int get_max_k(int *array, int low, int high, int index)
{
    if (low > high)
        return -1;
    int middle_index = sort(array, low, high);
    if (middle_index == index - 1)
    {
        return array[middle_index];
    } else if (middle_index < index - 1){
        return get_max_k(array, middle_index + 1, high, index);
    } else {
        return get_max_k(array, low, middle_index - 1, index);
    }
}
