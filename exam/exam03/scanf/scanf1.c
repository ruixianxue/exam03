#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

// Helper to skip whitespace
void skip_whitespace()
{
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (!isspace(c))
		{
			ungetc(c, stdin); // put back the non-whitespace character
			break;
		}
	}
}

// Read a single character
int scan_char(char *out)
{
	return read(STDIN_FILENO, out, 1);
}

// Read an integer
int scan_int(int *out)
{
	char buffer[100];
	int i = 0;
	char c;

	skip_whitespace();
	while (read(STDIN_FILENO, &c, 1) == 1 && (isdigit(c) || c == '-' || c == '+'))
	{
		buffer[i++] = c;
		if (i >= 99) break;
	}
	buffer[i] = '\0';
	*out = atoi(buffer);
	return 1;
}

// Read a string
int scan_string(char *out, int max_len)
{
	char c;
	int i = 0;

	skip_whitespace();
	while (read(STDIN_FILENO, &c, 1) == 1 && !isspace(c))
	{
		if (i < max_len - 1)
			out[i++] = c;
	}
	out[i] = '\0';
	return 1;
}

// Format: "%d%c%s", supports any combination
int ft_scanf(const char *format, ...)
{
	va_list ap;
	int matched = 0;
	va_start(ap, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int *ip = va_arg(ap, int*);
				matched += scan_int(ip);
			}
			else if (*format == 'c')
			{
				char *cp = va_arg(ap, char*);
				matched += scan_char(cp);
			}
			else if (*format == 's')
			{
				char *sp = va_arg(ap, char*);
				matched += scan_string(sp, 100);
			}
			else
			{
				// Unsupported specifier
				write(2, "Unsupported format\n", 20);
				va_end(ap);
				return -1;
			}
		}
		format++;
	}
	va_end(ap);
	return matched;
}

int main()
{
	int age;
	char gender;
	char name[100];

	printf("Enter age, gender, and name: ");
	ft_scanf("%d %c %s", &age, &gender, name);
	printf("You entered: %d %c %s\n", age, gender, name);
	return 0;
}
