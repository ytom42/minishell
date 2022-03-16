/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:30:14 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/15 21:36:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"
#include "expansion.h"

static t_cmd_type
	get_cmd_type(char *cmd)
{
	if (*cmd == '/')
		return (ABSOLUTE);
	else if (ft_strchr(cmd, '/'))
		return (RELATIVE);
	else
		return (COMMAND);
}

void
	create_cmd_path(char **split_paths, char **executable_path, char *cmd)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	while (split_paths[++i])
	{
		if (path)
			free_set((void **)&path, NULL);
		path = join_path(split_paths[i], cmd);
		if (check_executable_cmd(path))
		{
			*executable_path = ft_strdup(path);
			if (!(*executable_path))
				error_exit(NULL);
			break ;
		}
	}
	free_set((void **)&path, NULL);
}

char
	*search_cmd_path(char *cmd)
{
	char	*value;
	char	**paths;
	char	*executable_path;

	executable_path = NULL;
	value = get_env_value("PATH");
	if (!ft_strcmp(value, ""))
	{
		executable_path = ft_strdup(cmd);
		if (!executable_path)
			error_exit(NULL);
		return (executable_path);
	}
	paths = split_value(value, ':');
	if (!paths)
		error_exit(NULL);
	create_cmd_path(paths, &executable_path, cmd);
	instant_free(paths);
	return (executable_path);
}

static void
	check_cmd_path(const char *cmd, const char *path)
{
	if (path == NULL)
	{
		print_error_msg("command not found", (char *)cmd);
		exit(CMD_NOT_FND);
	}
}

char
	*create_executable_path(char *cmd)
{
	t_cmd_type	type;
	char		*path;

	if (!cmd)
		return (NULL);
	type = get_cmd_type(cmd);
	if (type == COMMAND)
		path = search_cmd_path(cmd);
	else
	{
		path = ft_strdup(cmd);
		if (!path)
			error_exit(NULL);
	}
	check_cmd_path(cmd, path);
	return (path);
}
