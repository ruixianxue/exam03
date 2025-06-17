/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function to swap characters
void	swap(char *x, char *y)
{
	char	temp = *x;

	*x = *y;
	*y = temp;
}

// recursive function to generate permutations
// str is the current string to permute
// left is the index of the character to fix in the current recursion level
// right is the total length of the string
void	permute(char *str, int left, int right)
{
	if (left == right) // when left == right, you've fixed all characters -> print this permitation
		puts(str); // print the permutation
	else
	{
		int	i = left; // initialize i for recursion
		while (i < right) // loop through all characters from left to right - 1
		{
			swap(&str[left], &str[i]); // swap the current index with left
			permute(str, left + 1, right); // recur for the rest
			swap(&str[left], &str[i]);  // backtrack to restore original string
			i++; // move to the next index
		}
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return 1;
	}
	char *input = strdup(argv[1]); // duplicate the input string
	permute(input, 0, strlen(input)); // generate permutations
	free(input); // free the allocated memory
	return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *x, char *y)
{
	char temp = *x;
	*x = *y;
	*y = temp;
}

int factorial(int n)
{
	if (n <= 1)
		return 1;
	return n * factorial(n - 1);
}

/*
This recursively generates all permutations of the string.

    str: the string to permute

    left: current fixed character index

    right: length of the string

    perms: the array where all permutations are stored

    index: tracks where to store the next permutation
*/
int collect_perm(char *str, int left, int right, char **perms, int index)
{
	if (left == right)
	{
		perms[index] = strdup(str);
		return index + 1;
	}
	int i = left;
	while (i < right)
	{
		swap(&str[left], &str[i]);
		index = collect_perm(str, left + 1, right, perms, index);
		swap(&str[left], &str[i]);
		i++;
	}
	return index;
}

void print_vertical(char **perms, int n)
{
	int rows = factorial(n - 1);
	int cols = n;
	int i = 0;
	while (i < rows)
	{
		int j = 0;
		while (j < cols)
		{
			printf("%s", perms[i + j * rows]);
			if (j < cols - 1)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("\n");
		return 0;
	}

	char *input = strdup(argv[1]);
	int len = strlen(input);
	int total = factorial(len);

	char **perms = malloc(sizeof(char *) * (total + 1));
	if (!perms)
		return 1;

	collect_perm(input, 0, len, perms, 0);
	print_vertical(perms, len);

	for (int i = 0; i < total; i++)
		free(perms[i]);
	free(perms);
	free(input);
	return 0;
}
