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

// 用于字典序排序
int cmp_str(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

// perm递归辅助函数：无循环版
int collect_perm_rec(char *str, int left, int right, char **perms, int index, int i)
{
	if (i == right)
		return index;
	swap(&str[left], &str[i]);
	index = collect_perm(str, left + 1, right, perms, index);
	swap(&str[left], &str[i]);
	return collect_perm_rec(str, left, right, perms, index, i + 1);
}

// 主递归函数：收集排列
int collect_perm(char *str, int left, int right, char **perms, int index)
{
	if (left == right)
	{
		perms[index] = strdup(str);
		return index + 1;
	}
	return collect_perm_rec(str, left, right, perms, index, left);
}

// 打印某一行（递归打印列）
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

// 递归打印所有行
void print_rows(char **perms, int rows, int cols, int row)
{
	if (row == rows)
		return;
	print_cols(perms, rows, cols, row, 0);
	print_rows(perms, rows, cols, row + 1);
}

// 递归释放内存
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
	int total = factorial(len);
	int rows = factorial(len - 1);

	char **perms = malloc(sizeof(char *) * total);
	if (!perms)
		return 1;

	collect_perm(input, 0, len, perms, 0);

	// 对排列结果排序，确保纵列排列有序
	qsort(perms, total, sizeof(char *), cmp_str);

	print_rows(perms, rows, len, 0);

	free_perms(perms, total, 0);
	free(perms);
	free(input);
	return 0;
}
