/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:28:04 by sko               #+#    #+#             */
/*   Updated: 2019/09/29 22:11:48 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	get next line is a function that reads a file line by line
**	return 1 when it read a line
**	return 0 when it finished reading a file
**	return -1 when an error occurs
*/

#include "libft.h"
#include <stdio.h>

char	*ft_sub_free(char **line, char **str, int fd, int size)
{
	char	*tmp;

	*line = ft_strsub(str[fd], 0, size);
	tmp = ft_strdup(str[fd] + size + 1);
	free(str[fd]);
	return (tmp);
}

int		ft_read_line(char **str, char **line, int fd)
{
	int		size;

	size = 0;
	while (str[fd][size] != '\n' && str[fd][size] != '\0')
		size++;
	if (str[fd][size] == '\n')
	{
		str[fd] = ft_sub_free(line, str, fd, size);
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (str[fd][size] == '\0')
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

char	*ft_join_free(char **str, int fd, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(str[fd], buf);
	free(str[fd]);
	return (tmp);
}

int		check_finish_or_error(char **str, int fd, int red, char **line)
{
	if (red == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	else if (red < 0)
		return (-1);
	else
		return (ft_read_line(str, line, fd));
}

int		get_next_line(const int fd, char **line)
{
	static char	*str[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	int			red;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((red = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[red] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		str[fd] = ft_join_free(str, fd, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (check_finish_or_error(str, fd, red, line));
}
