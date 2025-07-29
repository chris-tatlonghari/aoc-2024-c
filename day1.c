#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

#define INPUT_SIZE 1000

struct hash_entry {
    int key;
    int value;
    UT_hash_handle hh;  // makes this hashable
};

struct hash_entry *hash_table = NULL;

// Add entry
void add_entry(int key, int value) {
    struct hash_entry *entry = malloc(sizeof(struct hash_entry));
    entry->key = key;
    entry->value = value;
    HASH_ADD_INT(hash_table, key, entry);
}

// Find entry
struct hash_entry* find_entry(int key) {
    struct hash_entry *entry;
    HASH_FIND_INT(hash_table, &key, entry);
    return entry;
}

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
        struct hash_entry *entry = find_entry(list2[i]);
        if (entry) {
            entry->value++;
        } else {
            add_entry(list2[i], 1);
        }
    }
    
    printf("Part 1 solution is: %d\n", sum);

    int similarity_score = 0;
    for (int i = 0; i < count; i++) {
        struct hash_entry *entry = find_entry(list1[i]);
        if (entry) {
            similarity_score += list1[i] * entry->value;
        }
    }

    printf("Part 2 solution is: %d\n", similarity_score);



    return 0;
}
