/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:38:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/04 14:41:42 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "libft.h"
#include "expansion.h"
#include <string.h>
#include <errno.h>

extern t_master	g_master;

static char
	*set_destination_path(char **args)
{
	t_environ	*home;
	size_t		i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
	{
		home = get_env("HOME");
		if (!home)
		{
			print_error_msg("HOME not set", "cd");
			return (NULL);
		}
		if (!home->value)
			return ("");
		return (home->value);
	}
	return (args[1]);
}

static bool
	request_env_path(char **args, char *path)
{
	if (args[1] == NULL || args[1][0] == '/')
		return (FALSE);
	if (!ft_strncmp(path, ".", 1)
		|| !ft_strncmp(path, "..", 2)
		|| !ft_strncmp(path, "./", 2)
		|| !ft_strncmp(path, "../", 3))
		return (FALSE);
	return (TRUE);
}

static char
	*change_dir_split_cdpath(char **split_cdpath, char *path)
{
	size_t	i;
	char	*join_path;

	join_path = NULL;
	i = -1;
	while (split_cdpath[++i])
	{
		if (!ft_strlen(split_cdpath[i]))
			join_path = ft_strdup(path);
		else
			join_path = ft_strjoin(split_cdpath[i], path);
		if (!join_path)
			error_exit(NULL);
		if (change_dir(join_path))
			break;
		free_set((void **)&join_path, NULL);
	}
	free_set((void **)&join_path, NULL);
	if (split_cdpath[i])
		return (split_cdpath[i]);
	return (NULL);
}

static bool
	change_dir_env_path(char *path)
{
	bool	res;
	char	**split_cdpath;
	char	*success_path;
	char	*pwd;

	res = TRUE;
	split_cdpath = split_value(get_env_value("CDPATH"), ':');
	if (!split_cdpath)
		error_exit(NULL);
	success_path = change_dir_split_cdpath(split_cdpath, path);
	if (!success_path)
		res = FALSE;
	pwd = get_env_value("PWD");
	if (res && ft_strlen(success_path))
		ft_putendl_fd(pwd, STDOUT_FILENO);
	free_set((void **)&pwd, NULL);
	instant_free(split_cdpath);
	return (res);
}

int
	exec_cd(char **args)
{
	char	*path;

	path = set_destination_path(args);
	if (!path)
		return (EXIT_FAILURE);
	if (request_env_path(args, path))
	{
		if (change_dir_env_path(path))
			return (EXIT_SUCCESS);
	}
	if (change_dir(path))
		return (EXIT_SUCCESS);
	print_filename_error(strerror(errno), "cd", path);
	return (EXIT_FAILURE);
}
