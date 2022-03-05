/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:38:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/05 17:54:26 by kfumiya          ###   ########.fr       */
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

int
	exec_cd(char **args)
{
	char	*path;

	path = set_destination_path(args);
	if (!path)
		return (EXIT_FAILURE);
	if (change_dir(path))
		return (EXIT_SUCCESS);
	print_filename_error(strerror(errno), "cd", path);
	return (EXIT_FAILURE);
}
