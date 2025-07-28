#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1000

int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    FILE *file = fopen("day1.txt", "r");
    int list1[INPUT_SIZE], list2[INPUT_SIZE];
    int count = 0, sum = 0;

    if (file != NULL) {
        char buffer[100];

        while(fgets(buffer, sizeof(buffer), file)) {
            int num1, num2;
            if (sscanf(buffer, "%d %d", &num1, &num2) == 2) {
                list1[count] = num1;
                list2[count] = num2;
            }
            count++;
        }

        fclose(file);
    }

    qsort(list1, count, sizeof(int), compare_asc);
    qsort(list2, count, sizeof(int), compare_asc);

    for (int i = 0; i < INPUT_SIZE; i++) {
        sum += abs(list1[i] - list2[i]);
    }
    
    printf("Part 1 solution is: %d\n", sum);

    return 0;
}
