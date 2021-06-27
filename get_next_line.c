#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char		buf[11];
	int			byte_was_read;
	char		*p_n;
	int			flag;
	static char	*reaminder;

	if (fd < 0 || line == NULL ||  BUFFER_SIZE <= 0)
		return (-1);
	flag = 1;
	if (reaminder)
		*line = ft_strdup(reaminder)
	else
		*line = ft_bzero(2);
	// *line = ft_strnew(1);//аллоцирует память под то количество, которое мы просим и нуль терминат, и заполняет её нулями
	while (flag && (byte_was_read = read(fd, buf, 10)))
	{
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			flag = 0;
			p_n++;
			reaminder = ft_strdup(p_n);
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

	fd = open("text.txt", O_RDONLY) == -1;
	while ((i = get_next_line(fd, &line)))
	{
		printf ("i = %d %s\n", i, line);
		free (line);
	}
	printf ("i = %d %s\n", i, line);
	close(fd);
	free(line);
	return (0);
}
