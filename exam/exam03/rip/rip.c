#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 100

char input[MAX_LEN];
char current[MAX_LEN];
bool seen[MAX_LEN][MAX_LEN]; // To skip redundant calls
int min_remove = -1;

// Check if a string is valid (parentheses are balanced)
bool is_valid(const char *str)
{
	int balance = 0;
	while (*str)
	{
		if (*str == '(')
			balance++;
		else if (*str == ')')
		{
			if (balance == 0)
				return false;
			balance--;
		}
		str++;
	}
	return balance == 0;
}

void print_result(char *str, int len)
{
	str[len] = '\0';
	puts(str);
}

void backtrack(int i, int j, int l_rem, int r_rem, int open)
{
	if (i == (int)strlen(input))
	{
		if (l_rem == 0 && r_rem == 0 && open == 0)
			print_result(current, j);
		return;
	}
	if (input[i] == '(')
	{
		if (l_rem > 0)
			backtrack(i + 1, j, l_rem - 1, r_rem, open); // remove (
		current[j] = '(';
		backtrack(i + 1, j + 1, l_rem, r_rem, open + 1); // keep (
	}
	else if (input[i] == ')')
	{
		if (r_rem > 0)
			backtrack(i + 1, j, l_rem, r_rem - 1, open); // remove )
		if (open > 0)
		{
			current[j] = ')';
			backtrack(i + 1, j + 1, l_rem, r_rem, open - 1); // keep )
		}
	}
	else
	{
		current[j] = input[i];
		backtrack(i + 1, j + 1, l_rem, r_rem, open);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		puts("");
		return 0;
	}
	strncpy(input, argv[1], MAX_LEN - 1);
	input[MAX_LEN - 1] = '\0';

	int l_rem = 0, r_rem = 0;
	for (int i = 0; input[i]; i++)
	{
		if (input[i] == '(')
			l_rem++;
		else if (input[i] == ')')
		{
			if (l_rem > 0)
				l_rem--;
			else
				r_rem++;
		}
	}
	backtrack(0, 0, l_rem, r_rem, 0);
	return 0;
}