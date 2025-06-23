#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int collect_perm_rec(char *str, int left, int right, char **perms, int index, int i);
int collect_perm(char *str, int left, int right, char **perms, int index);

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

// 字典序比较
int cmp_str(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

// 判断当前字符是否已在 [left, curr) 中出现（用于去重）
int has_duplicate(char *str, int start, int curr)
{
	if (start == curr)
		return 0;
	if (str[start] == str[curr])
		return 1;
	return has_duplicate(str, start + 1, curr);
}

// 递归生成排列（避免重复）
int collect_perm_rec(char *str, int left, int right, char **perms, int index, int i)
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

int collect_perm(char *str, int left, int right, char **perms, int index)
{
	if (left == right)
	{
		perms[index] = strdup(str);
		return index + 1;
	}
	return collect_perm_rec(str, left, right, perms, index, left);
}

void print_cols(char **perms, int rows, int cols, int row, int col)
{
	if (col == cols)
	{
		printf("\n");
		return;
	}
	printf("%s", perms[row + col * rows]);
	if (col < cols - 1)
		printf(" ");
	print_cols(perms, rows, cols, row, col + 1);
}

void print_rows(char **perms, int rows, int cols, int row)
{
	if (row == rows)
		return;
	print_cols(perms, rows, cols, row, 0);
	print_rows(perms, rows, cols, row + 1);
}

void free_perms(char **perms, int total, int i)
{
	if (i == total)
		return;
	free(perms[i]);
	free_perms(perms, total, i + 1);
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
	int total = factorial(len); // 最大数量
	char **perms = malloc(sizeof(char *) * total);
	if (!perms)
		return 1;

	int real_total = collect_perm(input, 0, len, perms, 0); // generate only unique permutations
	qsort(perms, real_total, sizeof(char *), cmp_str); // sort them

	int rows = real_total / len; // 根据实际数量来排版
	print_rows(perms, rows, len, 0);

	free_perms(perms, real_total, 0);
	free(perms);
	free(input);
	return 0;
}
