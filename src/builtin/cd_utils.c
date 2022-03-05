/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:33:58 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/05 18:01:10 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <errno.h>

extern t_master	g_master;

static char
	*set_cd_path(char *arg, bool *is_canonical)
{
	char	*canonical_path;
	char	*physical_path;
	char	*tmp_pwd;

	tmp_pwd = get_env_value("PWD");
	if (*arg == '/')
		physical_path = ft_strdup(arg);
	else
		physical_path = join_path(tmp_pwd, arg);
	free_set((void **)&tmp_pwd, NULL);
	if (!physical_path)
		error_exit(NULL);
	canonical_path = path_canonicalisation(physical_path);
	if (canonical_path)
	{
		free_set((void **)&physical_path, NULL);
		*is_canonical = TRUE;
		return (canonical_path);
	}
	free_set((void **)&canonical_path, NULL);
	*is_canonical = FALSE;
	return (physical_path);
}

static char
	*get_new_pwd(char *cd_path, bool is_canonical, bool is_abs_path)
{
	char	*new_pwd;

	if (is_abs_path)
	{
		if (!is_canonical)
			new_pwd = get_cwd_path("cd");
		if (is_canonical || !new_pwd)
		{
			new_pwd = ft_strdup(cd_path);
			if (!new_pwd)
				error_exit(NULL);
		}
	}
	else
	{
		new_pwd = get_cwd_path("cd");
		if (!new_pwd)
		{
			new_pwd = ft_strdup(cd_path);
			if (!new_pwd)
				error_exit(NULL);
		}
	}
	return (new_pwd);
}

static int
	change_directory(char *cd_path, char *arg, bool is_canonical)
{
	int		res;
	int		err;
	char	*pwd;

	pwd = NULL;
	res = chdir(cd_path);
	if (!res)
	{
		pwd = get_new_pwd(cd_path, is_canonical, TRUE);
		update_env("PWD", pwd, FALSE);
		return (res);
	}
	err = errno;
	res = chdir(arg);
	if (!res)
	{
		pwd = get_new_pwd(cd_path, is_canonical, FALSE);
		update_env("PWD", pwd, FALSE);
		return (res);
	}
	errno = err;
	res = EXIT_FAILURE;
	return (res);
}

bool
	change_dir(char *dir_path)
{
	char	*path;
	int		res;
	bool	is_canonical;
	char	*oldpwd;

	oldpwd = get_cwd_path("cd");
	path = set_cd_path(dir_path, &is_canonical);
	res = change_directory(path, dir_path, is_canonical);
	if (!res)
		update_env("OLDPWD", oldpwd, FALSE);
	free_set((void **)&path, NULL);
	if (!res)
		return (TRUE);
	return (FALSE);
}
