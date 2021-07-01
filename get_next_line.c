#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*remainder;
	char		*p_n;
	int			byte_was_read;
	char		*tmp;

	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1)
		return (-1);
	while (1)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		buf[byte_was_read] = '\0';
		if (byte_was_read == -1)
			return (-1);
		if (!remainder)
			remainder = ft_strdup(buf);
		else
		{
			tmp = remainder;
			remainder = ft_strjoin(remainder, buf);
			free(tmp);
		}
		p_n = ft_strchr(remainder, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(remainder);
			p_n++;
			tmp = remainder;
			remainder = ft_strdup(p_n);
			free(tmp);
			return (1);
		}
		else
		{
			*line = ft_strdup(remainder);
			free(remainder);
			remainder = NULL;
			return (0);
		}
	}
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("43_no_nl", O_RDONLY);
// 	while ((i = get_next_line(fd, &line)))
// 	{
// 		printf("i = %d %s\n", i, line);
// 		free(line);
// 	}
// 	close(fd);
// 	free(line);
// 	return (0);
// }
