/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:28:26 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/19 10:57:48 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	save_fd(int fd, char **s, char *move, char *buf)
{
	move = ft_strjoin(s[fd], buf);
	if (!move)
		return (esc(s, fd, -1));
	free(s[fd]);
	s[fd] = move;
	return (1);
}

static int
	check_read(int fd, char *buf)
{
	int	endr;

	endr = read(fd, buf, BUFFER_SIZE);
	if (endr < 1)
		return (-1);
	buf[endr] = '\0';
	return (1);
}

static int
	end_read(int fd, char **line, char **s, char *buf)
{
	int		endr;
	char	*move;

	while (1)
	{
		endr = check_read(fd, buf);
		move = ft_strchr(buf, '\n');
		if (endr < 1)
			break ;
		if (move)
		{
			if (end_n(move, line, &s[fd], buf) == -1)
				return (esc(s, fd, -1));
			return (1);
		}
		if (endr < BUFFER_SIZE)
		{
			if (end_null(line, &s[fd], buf) == -1)
				return (esc(s, fd, -1));
			return (0);
		}
		if (save_fd(fd, s, move, buf) == -1)
			return (-1);
	}
	return (2);
}

static int
	read_fd(int fd, char **line, char **s)
{
	int		flag;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (esc(s, fd, -1));
	if (!s[fd])
	{
		s[fd] = ft_strdup("");
		if (!s[fd])
			return (esc(s, fd, -1));
	}
	flag = end_read(fd, line, s, buf);
	if (flag != 2)
		return (flag);
	free(buf);
	buf = NULL;
	*line = ft_strdup(s[fd]);
	if (!(*line))
		return (esc(s, fd, -1));
	return (esc(s, fd, 0));
}

int
	get_next_line(int fd, char **line)
{
	static char	*s[256];
	char		*move;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE == 0)
		return (esc(s, fd, -1));
	if (s[fd])
	{
		move = ft_strchr(s[fd], '\n');
		if (move)
		{
			*move = '\0';
			*line = ft_strdup(s[fd]);
			if (!(*line))
				return (esc(s, fd, -1));
			tmp = ft_strdup(++move);
			if (!(tmp))
				return (esc(s, fd, -1));
			free(s[fd]);
			s[fd] = tmp;
			return (1);
		}
	}
	return (read_fd(fd, line, s));
}
