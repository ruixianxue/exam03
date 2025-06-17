#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *ft_strdup(char *str)
{
	int i;
	char *new;
	i = 0;
	if (!str)
	{
		return (NULL);
	}
	while (str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	i = 0;
	while(str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
char *get_next_line(int fd)
{
	int i;
	static int buffer_pos = 0;
	static int buffer_read = 0;
	static char buffer[BUFFER_SIZE];
	char line[70000];
	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		line[i] = buffer[buffer_pos++];
		if (line[i++] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}