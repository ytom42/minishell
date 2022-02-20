/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:23:27 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/18 19:12:56 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

static void
	require_front_slash(char *path, char **res)
{
	char	*complete;
	
	if (!path || !res || !*res)
		return ;
	if (!ft_strncmp(path, "//", 2) && path[2] != '/'
		&& ft_strncmp(*res, "//", 2))
	{
		cmplete = ft_strjoin("/", *res);
		if (!complete)
			error_exit(NULL);
		set_free((void **)res, NULL);
		*res = complete;
	}
}

char
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
		path_pos = ft_strcpy_forward(path_pos, '/');
		path_pos = ft_strcpy_forward(path_pos, elem);
	}
	return (path_pos);
}

bool
	edit_path(char **split, char **res)
{
	char	*start;
	char	*path_pos;
	size_t	i;

	start = *res;
	*start = '\0';
	path_pos = start;
	i = -1;
	while (split[++i])
	{
		path_pos = copy_path_elem(path_pos, split[i], start);
		if (path_pos == start)
			path_pos = ft_strcpy_forward(path_pos, "/");
		if (!is_directory(start))
			return (FALSE);
	}
	if (path_pos == start)
		path_pos = ft_strcpy_forward(path_pos, "/");
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
	res = malloc(sizeof(char *) * (ft_strlen(path) + 1));
	if (!split || !res)
		error_exit(NULL);
	if (!edit_path(split, &res))
		set_free((void **)&res, NULL);
	instant_free((split);
	require_front_slash(path, &res);
}
