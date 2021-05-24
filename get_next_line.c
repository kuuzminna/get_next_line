#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char	buf[11];
	int		byte_was_read;
	char	*p_n;
	int		flag;

	flag = 1;
	// *line = ft_strnew(1);//аллоцирует память под то количество, которое мы просим и нуль терминат, и заполняет её нулями
	*line = ft_bzero(2);
	while (flag && (byte_was_read = read(fd, buf, 10)))
	{
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			flag = 0;
		}
		*line = ft_strjoin(*line, buf);//склеивает лайн и буфер
	}
	return (0);
}

int	main(void)
{
	int		i;
	char	*line;
	int		fd;

	// while (get_next_line(4, &line))
	fd = open("text.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
}
