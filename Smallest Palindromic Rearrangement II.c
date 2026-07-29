#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to safely calculate unique permutations of remaining characters
long long get_ways(int counts[26]) {
    long long ways = 1;
    int current_len = 0;
    
    for (int i = 0; i < 26; i++) {
        if (counts[i] == 0) continue;
        for (int j = 1; j <= counts[i]; j++) {
            current_len++;
            ways = ways * current_len / j;
            // Cap to prevent integer overflow since k fits in a standard int
            if (ways > 2000000005LL) {
                return 2000000005LL;
            }
        }
    }
    return ways;
}

char* smallestPalindrome(char* s, int k) {
    int n = strlen(s);
    int total_counts[26] = {0};
    for (int i = 0; i < n; i++) {
        total_counts[s[i] - 'a']++;
    }
    
    // Determine the character counts for the first half
    int half_counts[26] = {0};
    char mid_char = '\0';
    for (int i = 0; i < 26; i++) {
        half_counts[i] = total_counts[i] / 2;
        if (total_counts[i] % 2 != 0) {
            mid_char = 'a' + i;
        }
    }
    
    int half_len = n / 2;
    
    // Check if the total possible permutations are fewer than k
    long long total_ways = get_ways(half_counts);
    if (total_ways < k) {
        char* empty_str = (char*)malloc(sizeof(char));
        empty_str[0] = '\0';
        return empty_str;
    }
    
    // Allocate memory for the resulting string
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';
    
    long long remaining_k = k;
    
    // Greedily build the first half
    for (int i = 0; i < half_len; i++) {
        for (int c = 0; c < 26; c++) {
            if (half_counts[c] > 0) {
                // Try placing character 'c' at position i
                half_counts[c]--;
                
                long long ways = get_ways(half_counts);
                if (remaining_k <= ways) {
                    result[i] = 'a' + c;
                    break; // Found the correct character for position i
                } else {
                    remaining_k -= ways;
                    half_counts[c]++; // Backtrack and try next character
                }
            }
        }
    }
    
    // Place the middle character if the total length is odd
    if (n % 2 != 0) {
        result[half_len] = mid_char;
    }
    
    // Mirror the first half to form the second half
    for (int i = 0; i < half_len; i++) {
        result[n - 1 - i] = result[i];
    }
    
    return result;
}
