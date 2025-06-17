#include "n_queens.h"

int	main(int argc, char **argv)
{
	int	n;
	int	*board;

	if (argc != 2)
		return 0;
	n = atoi(argv[1]);
	if (n < 1)
		return 0;
	board = malloc(n * sizeof(int));
	if (!board)
		return 0;
	solve(board, n, 0);
	return 0;
}

void	solve(int *board, int n, int col)
{
	int	row;

	if (col == n)
	{
		print_solution(board, n); // all queens are placed, print the solution
		return;
	}
	row = 0;
	while (row < n) // try each row in the current column
	{
		if (is_safe(board, col, row)) // check if placing a queen at (row, col) is safe
		{
			board[col] = row; // place the queen
			solve(board, n, col + 1); // recurse to next column
		}
		row++;
	}
}

int	is_safe(int *board, int col, int row)
{
	int	i;
	int	diff;

	i = 0;
	while (i < col) // iterate over already-placed queens in earlier columns
	{
		if (board[i] == row) // same row check
			return 0;
		diff = row - board[i]; // compute absolute difference in rows
		if (diff < 0)
			diff = -diff;
		if (diff == col - i) // diagonal check, if row difference == column difference, they are on the same diagonal
			return 0;
		i++;
	}
	return 1;
}

void print_solution(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i > 0)
			printf(" ");
		printf("%d", board[i]);
		i++;
	}
	printf("\n");
}