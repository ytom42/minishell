/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:44:56 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/25 14:17:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"
#include "libft.h"

bool
	is_command(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) < 0)
		return (FALSE);
	if (S_ISDIR(buf.st_mode))
		return (FALSE);
	return (TRUE);
}

bool
	is_executable(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
		return (FALSE);
	if ((buf.st_mode & S_IXUSR) != S_IXUSR)
		return (FALSE);
	if ((buf.st_mode & S_IRUSR) != S_IRUSR)
		return (FALSE);
	return (TRUE);
}

bool
	check_executable_cmd(char *path)
{
	if (is_directory(path))
		return (FALSE);
	if (!is_command(path))
		return (FALSE);
	if (!is_executable(path))
		return (FALSE);
	return (TRUE);
}
