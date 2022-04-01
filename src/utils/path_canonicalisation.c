/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:23:27 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/01 15:26:28 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "execute.h"

static char
	*copy_path_elem(char *path_pos, char *elem, char *start)
{
	if (!ft_strcmp(elem, ".."))
	{
		path_pos = ft_strrchr(start, '/');
		if (!path_pos)
			path_pos = start;
		*path_pos = '\0';
	}
	else if (ft_strcmp(elem, "."))
	{
		path_pos = ft_strcpy_forward(path_pos, "/");
		path_pos = ft_strcpy_forward(path_pos, elem);
	}
	return (path_pos);
}

static bool
	edit_path(char **split, char *res)
{
	char	*start;
	char	*path_pos;
	size_t	i;

	start = res;
	start[0] = '\0';
	path_pos = start;
	i = -1;
	while (split[++i])
	{
		path_pos = copy_path_elem(path_pos, split[i], start);
		if (!is_directory(start))
			return (FALSE);
	}
	return (TRUE);
}

char
	*path_canonicalisation(char *path)
{
	char	**split;
	char	*res;

	if (!path)
		return (NULL);
	split = ft_split(path, '/');
	res = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (!split || !res)
		error_exit(NULL);
	if (!edit_path(split, res))
		free_set((void **)&res, NULL);
	instant_free((split));
	return (res);
}
