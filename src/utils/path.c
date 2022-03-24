/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:04:50 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/24 20:21:58 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "execute.h"

char
	*join_path(char *front, char *back)
{
	char	*res;
	char	*tmp;
	size_t	i;

	if (!front || !back)
		return (NULL);
	res = NULL;
	tmp = NULL;
	tmp = ft_strjoin(front, "/");
	if (!tmp)
		error_exit(NULL);
	i = ft_strlen(tmp);
	if (i >= 2 && tmp[i - 2] == '/')
		tmp[i - 1] = '\0';
	res = ft_strjoin(tmp, back);
	if (!res)
		error_exit(NULL);
	free_set((void **)&tmp, NULL);
	return (res);
}

bool
	is_directory(const char *path)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) == -1)
		return (FALSE);
	if (S_ISDIR(stat_buf.st_mode))
		return (TRUE);
	return (FALSE);
}
