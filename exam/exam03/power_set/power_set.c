#include "power_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int target;     // the target sum we're trying to reach with subsets
static int *nums;      // the input set of numbers (from command line)
static int n;          // the number of elements in the input set
static int *subset;    // temporarily holds the current subset being explored
static int subset_size;// current size of the subset array

/*
 * backtrack parcourt récursivement tous les sous-ensembles
 * en commençant à l'indice 'start', en gardant la somme actuelle
 * current_sum. Dès que current_sum == target, on affiche subset.
 * start: where to begin the subset search from
 * current sum: the sum of the currently formed subset
 */
void backtrack(int start, int current_sum) {
    if (current_sum == target) { // if the current subset's sum equals the target
        /* afficher la sous-suite (ou ligne vide si subset_size==0) */
        if (subset_size == 0) { // print empty line for empty subset
            printf("\n");
        } else { // otherwise, print numbers separated by spaces
            printf("%d", subset[0]); 
            for (int i = 1; i < subset_size; i++)
                printf(" %d", subset[i]);
            printf("\n");
        }
    }
    for (int i = start; i < n; i++) { // recursively build subsets
        subset[subset_size++] = nums[i]; // include nums[i] in subset
        backtrack(i + 1, current_sum + nums[i]); // recur with next index
        subset_size--; // backtrack (remove last)
    }
}

int main(int argc, char **argv) {
    if (argc < 2)
        return 0;

    /* read target sum */
    target = atoi(argv[1]);

    /* determine number of set elements */
    n = argc - 2;

    /* allocate memory */
    nums = malloc(sizeof(int) * n);
    if (!nums) exit(1);

    subset = malloc(sizeof(int) * n);
    if (!subset) exit(1);

    /* convert command-line strings to integers */
    for (int i = 0; i < n; i++)
        nums[i] = atoi(argv[i + 2]);

    subset_size = 0;
    backtrack(0, 0); // start recursion

    free(nums);
    free(subset);
    return 0;
}