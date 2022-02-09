/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:30:55 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/09 14:30:56 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 100
// #endif

static int	ft_rewrite_remainder(char **line, char **remainder,
								int byte_was_read)
{
	char	*tmp;
	char	*p_n;

	p_n = ft_strchr(*remainder, '\n');
	if (p_n)
	{
		*p_n++ = '\0';
		*line = ft_strdup(*remainder);
		tmp = *remainder;
		*remainder = ft_strdup(p_n);
		free(tmp);
		return (1);
	}
	if (byte_was_read == 0)
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (0);
	}
	return (-1);
}

static char	*check_remainder(const char *buf, char *remainder)
{
	char	*tmp;

	if (!remainder)
		remainder = ft_strdup(buf);
	else
	{
		tmp = remainder;
		remainder = ft_strjoin(remainder, buf);
		free(tmp);
	}
	return (remainder);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*remainder;
	int			byte_was_read;
	int			returned;

	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1)
		return (-1);
	while (1)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		buf[byte_was_read] = '\0';
		if (byte_was_read == -1)
			return (-1);
		remainder = check_remainder(buf, remainder);
		returned = ft_rewrite_remainder(line, &remainder, byte_was_read);
		if (returned == 0 || returned == 1)
			return (returned);
	}
	return (0);
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
