#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	swap(char *x, char *y)
{
	char tmp = *x;
	*x = *y;
	*y = tmp;
}

int	factorial(int n)
{
	if (n <= 1)
		return 1;
	return (n * factorial(n - 1));
}

int	cmp_str(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

int	has_duplicate(char **str, int start, int curr)
{
	if (start == curr)
		return 0;
	if (str[start] == str[curr])
		return 1;
	return has_duplicate(str, start + 1, curr);
}

int	collect_perm_rec(char *str, int left, int right, char **perms, int index, int i)
{
	if (i == right)
		return index;
	if (!has_duplicate(str, left, i))
	{
		swap(&str[left], &str[i]);
		index = collect_perm(str, left + 1, right, perms, index);
		swap(&str[left], &str[i]);
	}
	return collect_perm_rec(str, left, right, perms, index, i + 1);

}

int	collect_perm(char *str, int left, int right, char **perms, int index)
{
	if (left == right) // when reach the end of a string
	{
		perms[index] = strdup(str); // save it in the index of perms
		return index + 1; // move to the next slot
	}
	return collect_perm_rec(str, left, right, perms, index, left);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\n");
		return 1;
	}

	char *input = strdup(argv[1]); // duplicated argv[1] as the input string
	if (!input)
		return 0;
	int	len = strlen(input); // get the length of the string
	int total = factorial(len); // maximum amount of permutations
	char **perms = malloc(sizeof(char *) * total); // allocated (total) spaces for permutations
	if (!perms)
		return 1;
	
	int	real_total = collect_perm(input, 0, len, perms, 0);
	qsort(perms, real_total, sizeof(char *), cmp_str);

	int	rows = real_total / len;
	print_rows(perms, rows, len, 0);

	free_perms(perms, real_total, 0);
	free(perms);
	free(input);
	return 0;
}