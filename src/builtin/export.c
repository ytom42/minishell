/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:19:26 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/31 19:55:43 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "expansion.h"

extern t_master	g_master;

void
	print_env(t_environ *env)
{
	char	*expand_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		expand_value = create_value_str(env->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(expand_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(expand_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int
	set_envs(char **args)
{
	int		i;
	int		res;
	bool	add_request;
	char	*sep;
	char	*value;

	res = EXIT_SUCCESS;
	i = 0;
	while (args[++i])
	{
		split_key_value(args[i], &sep, &value, &add_request);
		if (is_valid_identifier(args[i]))
		{
			if (!sep)
				continue ;
			update_env(args[i], value, add_request, TRUE);
		}
		else
		{
			restore_arg(sep, add_request);
			print_identifier_error("export", args[i]);
			res = EXIT_FAILURE;
		}
	}
	return (res);
}

int
	declare_envs(void)
{
	t_environ	*envs;

	if (!g_master.environs)
		return (EXIT_SUCCESS);
	envs = dup_envs(g_master.environs);
	if (!envs)
		error_exit(NULL);
	sort_envs(&envs);
	g_master.tmp_env = envs;
	while (envs)
	{
		print_env(envs);
		envs = envs->next;
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
