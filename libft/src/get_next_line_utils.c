/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:12:57 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/19 08:26:47 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	esc(char **s, int fd, int flag)
{
	int	i;

	if (flag == -1)
	{
		i = -1;
		while (++i < 256)
		{
			if (s[i])
			{
				free(s[i]);
				s[i] = NULL;
			}
		}
	}
	if (flag == 0)
	{
		if (s[fd])
		{
			free(s[fd]);
			s[fd] = NULL;
		}
	}
	return (flag);
}

int
	end_n(char *move, char **line, char **sfd, char *buf)
{
	*move = '\0';
	*line = ft_strjoin(*sfd, buf);
	if (!(*line))
		return (-1);
	free(*sfd);
	*sfd = ft_strdup(++move);
	if (!(*sfd))
		return (-1);
	free(buf);
	buf = NULL;
	return (1);
}

int
	end_null(char **line, char **sfd, char *buf)
{
	*line = ft_strjoin(*sfd, buf);
	if (!(*line))
		return (-1);
	free(*sfd);
	free(buf);
	*sfd = NULL;
	buf = NULL;
	return (0);
}
