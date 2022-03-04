/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:04:50 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/03 15:09:33 by kfumiya          ###   ########.fr       */
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

// char
// 	**allocate_memory_parent(char *str)
// {
// 	char	**res;
// 	size_t	i;
// 	size_t	colon;

// 	colon = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == ':')
// 			colon++;
// 	}
// 	res = malloc(sizeof(char *) * (colon + 2));
// 	if (!res)
// 		error_exit(NULL);
// 	res[colon + 1] = NULL;
// 	return (res);
// }

// char
// 	*strdup_elem(char *elem, char default_str)
// {
// 	char	*res;
	
// 	if (!elem)
// 		return (NULL);
// 	if (!ft_strlen(elem))
// 		res = ft_strdup(default_str);
// 	else
// 		res = ft_strdup(elem);
// 	if (!res)
// 		error_exit(NULL);
// 	return (res);
// }

// char
// 	**separate_elem_colon(char *str, char *default_str)
// {
// 	char	**res;
// 	char	*elem_start;
// 	char	*elem_end;
// 	size_t	i;
// 	char	*dup_str;

// 	res = allocate_memory_parent(str);
// 	dup_str = ft_strdup(str);
// 	if (!dup_str)
// 		return (error_exit(NULL));
// 	elem_start = dup_str;
// 	elem_end = ft_strchr(elem_start, ':');
// 	i = 0;
// 	while (elem_end)
// 	{
// 		*elem_end = '\0';
// 		res[i] = strdup_elem(elem_start, default_str);
// 		i++;
// 		elem_start = elem_end + 1;
// 		elem_end = ft_strchr(elem_start, ':');
// 	}
// 	res[i] = strdup_elem(elem_start, default_str);
// 	set_free((void **)&dup_str, NULL);
// }
