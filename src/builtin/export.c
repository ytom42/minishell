/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:19:26 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 17:15:10 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "libft.h"

void
	sort_envs(t_environ *env)
{
	t_environ	*tmp;
	t_environ	*left;
	t_environ	*right;

	left = env;
	right = env->next;
	while (left)
	{
		while (right)
		{
			if (strcmp(left->key, right->key) > 0)
			{
				tmp = left;
				left = right;
				left = tmp;
			}
			right++;
		}
		left++;
	}
}

int
	set_env(char **args)
{
	int		i;
	int		res;
	char	**split;

	res = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		split = split_key_value(args[i]);
		if (!split || !ft_strcmp(split[0], ""))
		{
			print_identifier_error("export", args[i]);
			res = EXIT_FAILURE;
		}
		if (is_valid_idntifier(args[i]))
			update_env(split);
		else
		{
			instant_free(split);
			print_identifier_error("export", args[i]);
			res = EXIT_FAILURE;
		}
	}
	return (res);
}

int
	declare_envs(void)
{
	extern t_master	*master;
	t_environ		*envs;
	t_environ		*tmp;
	
	// リストのコピー
	envs = dup_envs(master->environs);
	// ソート
	sort_envs(envs);
	// 一覧表示
	while (envs)
	{
		print_env(envs);
		tmp = envs->next;
		free(envs);
		envs = tmp;
	}
	return (EXIT_SUCCESS);
}

int
	exec_export(char **args)
{
	if (args[1])
		return (set_envs(args));
	else
		return (declare_envs());
	return (EXIT_SUCCESS);
}
