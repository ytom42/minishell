/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:38:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 17:19:31 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

extern t_master	g_master;

char
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
	// 絶対パス、相対パスかの判定
	/* 
	絶対パスの処理
		パスの正規化
		移動（get_cwd）
		pwd,oldpwdのvalueの変更
	 */
	/* 
	相対パスの処理
		移動（get_cwd）
		pwd,oldpwdのvalueの変更
	 */
	return (EXIT_FAILURE);
}
