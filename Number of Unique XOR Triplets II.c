#include <stdbool.h>

int uniqueXorTriplets(int* nums, int numsSize) {
    bool seen_pair[2048] = {false};
    bool seen_triplet[2048] = {false};

    // Step 1: Compute all unique XOR values of pairs (i, j) where i <= j
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            seen_pair[nums[i] ^ nums[j]] = true;
        }
    }

    // Step 2: Combine pair XORs with a third element nums[k]
    for (int p = 0; p < 2048; p++) {
        if (seen_pair[p]) {
            for (int k = 0; k < numsSize; k++) {
                seen_triplet[p ^ nums[k]] = true;
            }
        }
    }

    // Step 3: Count unique triplet XOR values
    int count = 0;
    for (int i = 0; i < 2048; i++) {
        if (seen_triplet[i]) {
            count++;
        }
    }

    return count;
}
