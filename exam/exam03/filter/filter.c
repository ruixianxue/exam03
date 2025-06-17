#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void	ft_strcat(char *dst, char *src)
{
	int	dst_len;
	int	i = 0;

	dst_len = strlen(dst);
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
}
/* 比较字符串 s1 和 s2 的前 n 个字符。
如果 s1 < s2，返回负数；
如果 s1 == s2，返回 0；
如果 s1 > s2，返回正数 */
int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i] && i < n))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
//从标准输入（stdin）逐字符地读取输入内容，并把它们拼接成一个完整的字符串返回。它动态申请内存，直到用户停止输入（如按下 Ctrl+D 或输入结束）。
//ssize_t read(int fd, void *buf, size_t count);从文件描述符 fd 中读取最多 count 字节的数据，放入 buf 缓冲区中。; 返回实际读取的字节数；如果读取到文件末尾，返回0；如果出错，返回-1，并设置errno
char *read_str(void)
{
	char	buffer[2];
	char	*result;
	char	*tmp;
	int		readed;
	int		i;

	i = 0;
	readed = 0;
	result = calloc(1, 1); // start with empty string
	if (!result)
	{
		perror("Error");
		return (NULL);
	}
	while ((readed = read(STDIN_FILENO, buffer, 1)) > 0)
	{
		buffer[readed] = '\0'; // null-terminate the single char
		tmp = realloc(result, i + readed + 1);
		if (!tmp)
		{
			free(result);
			perror("Error");
			return (NULL);
		}
		result = tmp;
		result[i++] = buffer[0];
		result[i] = '\0'; // maintain null-terminated string
	}
	return (result);
}

char	*search_and_replace(char *str, char *needle)
{
	char	*res;
	int		needle_len;
	int		i;//for str
	int		j;//for the numbre of  needle
	int		r;//for res

	i = 0;
	j = 0;
	r = 0;
	needle_len = strlen(needle);
	if (!str || !needle || needle_len == 0)
		return (str);
	res = malloc (sizeof(char) * (strlen(str) + 1));
	if (res == NULL)
	{
		perror("Error");
		return (NULL);
	}	
	while (str[i])
	{
		if (ft_strncmp(&str[i], needle, needle_len) == 0)//如果存在与needle相同的字符串
		{
			if (j++ < needle_len)
				i += needle_len;//直接删除
			else
			{
				res[r++] = '*';
				res[r++] = '*';
				i += needle_len;
			}
		}
		else
			res[r++] = str[i++];
	}
	res[r] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	char	*input;
	char	*filtered;

	if (argc != 2)
	{
		printf("Usage: %s string\n", argv[0]);
		return (1);
	}
    // Read input from stdin
    input = read_str();
    if (!input) {
        return 1;
    }
    
    // Filter the input
    filtered = search_and_replace(input, argv[1]);
    if (!filtered) {
        return 1;
    }
    
    // Output the result
    printf("%s", filtered);
    
    // Clean up
    free(filtered);
    
    return 0;
}