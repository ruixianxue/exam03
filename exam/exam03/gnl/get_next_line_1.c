#include "get_next_line.h"


//1.strdup.c
// 1.1 compter la len
// 1.2 malloc
// 1.3 copier
// 1.4 return
//2. get_next_line
// 2.1 verifier si fd et BUFFER_SIZE est valide
// 2.3 lire le buffer
// 3.4 copier le buffer dans line
// 3.5 verifier si = '\n' ou '\0' si oui break
// 3.6 ajouter '\0' a la fin de line

char *ft_strdup(const char *src) {
	char *dest;
	int i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE]; // stores chunks read from fd, reused across calls
	static int buf_pos = 0; // current index in buffer
	static int buf_read = 0; // how many bytes were read last time from read()
	int i = 0; // index for filling line
	char line[70000]; // temporary buffer to accumulate characters

	if (fd < 0 || BUFFER_SIZE <= 0) // return early if the fd or buffer size if invalid
		return NULL;
	while (1) 
	{ // start an infinite loop to read and build the line
		if (buf_pos >= buf_read) // if all data has been consumed from the static buffer, refill it
		{
			buf_read = read(fd, buffer, BUFFER_SIZE);
			if (buf_read <= 0) 
			{
    			if (buf_read < 0)
       				return NULL; // read error
				if (buf_read == 0) 
				{
					buf_pos = 0;
        			buf_read = 0;
    			}
    			break;
			}
			buf_pos = 0;
		}
		line[i++] = buffer[buf_pos++]; // copy one character from buffer to line
		if (line[i - 1] == '\n') // if the character just copied is \n, stop
			break;
	}
	line[i] = '\0'; // null-terminate the string
	if (i == 0) // if no characters were read, return NULL
		return (NULL);
	return (ft_strdup(line)); // copy the result to a dynamically allocated string
}