#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

void	skip_input_space()
{
	int	ch; // declares a variable to store one character from input
	
	while ((ch = fgetc(stdin)) != EOF) // repeatedly reads one character from stdin using fgetc(), loop continues until EOF is reached or a non-whitespace character is encountered
	{
		if (ch != ' ' && ch != '\t' && ch != '\n') // check whether the character is not a space, tab, or newline
		{
			ungetc(ch, stdin); // if the character is not whitespace, it's pushed back into the input stream so it can be processed again later by another function
			break; // exits the loop after putting the non-whitespace character back
		}
	}
}

int	scan_char(va_list ap)
{
	char	*cPtr = va_arg(ap, char *); // retrive a char * from va_list
	int		ch = fgetc(stdin); //read one character from standard input using fgetc()
	
	if (ch != EOF) // if a character was successfully read, store it at the memory location pointed to by cPtr
	{
		*cPtr = ch;
		return 1;
	}
	return 0;
}

int	scan_int(va_list ap)
{
	int		*iPtr = va_arg(ap, int *); // retrive the next argument from va_list, which is expected to be a pointer to an int, this is where the scanned integer will be stored
	char	buffer[100]; // used to temporarily store digit characters as a string
	int		index = 0; // tracks how many digits have been stored
	int		ch; // holds each character read from stdin

	skip_input_space(); // skip whitespaces before reading the number, prevents reading invalid characters like spaces before the digits
	while (isdigit(ch = fgetc(stdin)) && index < sizeof(buffer) - 1) // reads characters one at a time from stdin, if the character is a digit (0-9), it's stored in buffer, stops when a non-digit is found or the buffer is full
	{
		buffer[index++] = ch;
	}
	if (index > 0) // check if at least one digit was read
	{
		buffer[index] = '\0'; // null-terminates the digit string
		*iPtr = atoi(buffer); // converts it to an integer using atoi, stores the result at the location pointed to by iPtr
		if (ch != EOF) // if the loop stopped on a non-digit(but valid) character, this character is pushed back to the input stream
		{
			ungetc(ch, stdin);
		}
		return 1;
	}
	return 0;
}

int	scan_string(va_list ap)
{
	char	*strPtr = va_arg(ap, char *); // retrives the next argument from the va_list, which should be a char * pointing to a pre-allocated buffer where the input string will be stored
	int		ch; // stores each character read from input
	int		index = 0; // keep track of where to insert the next character in strPtr

	skip_input_space(); // skips any leading whitespace so the string reading starts at the first non-space character
	while ((ch = fgetc(stdin)) != EOF && !isspace(ch) && index < 99) // read characters one at a time from stdin until EOF is reached, a whitespace character is found or maximum 99 characters are read to avoid buffer overflow
	{
		strPtr[index++] = ch; // store each character until a space
	}
	strPtr[index] = '\0'; // null-terminates the string
	if (index > 0) // if at least one character was read, return 1 
		return 1;
	else
		return 0;
}

int	receive_input(const char **format, va_list ap)
{
	if (**format == 'c')
	{
		return scan_char(ap);
	}
	else if (**format == 'd')
	{
		return scan_int(ap);
	}
	else if (**format == 's')
	{
		return (scan_string(ap));
	}
	else
	{
		return -1; // unsupported format
	}
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	int matched = 0;
	const char *ptr = format;

	va_start(ap, format);

	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++; // skip '%'
			if (*ptr == '\0') // format ends unexpectedly
				break;

			int res = receive_input(&ptr, ap);
			if (res == -1)
			{
				// unsupported format
				va_end(ap);
				return -1;
			}
			matched += res;
		}
		else
		{
			// Optional: skip literal characters (e.g. '(', '-', etc.)
			ptr++;
		}
	}

	va_end(ap);
	return matched;
}

int main()
{
	char c;
	char str[100];
	int num;

	printf("Enter a char, a string, and an integer:\n");
	int count = ft_scanf("%c%s%d", &c, str, &num);

	printf("Matched: %d\n", count);
	printf("Char: %c\nString: %s\nInteger: %d\n", c, str, num);

	return 0;
}
