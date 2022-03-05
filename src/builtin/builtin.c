/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:00:17 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/04 15:34:55 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int
	is_builtin_cmd(char **args)
{
	const char	*builtins[] = {
		"exit", "cd", "echo", "pwd", "env", "export", "unset", NULL
	};
	int			i;

	i = 0;
	if (!args[0])
		return (0);
	while (builtins[i])
	{
		if (!ft_strcmp(args[0], (char *)builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int
	exec_builtin_cmd(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (exec_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (exec_cd(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (exec_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (exec_export(args));
	if (!ft_strcmp(args[0], "unset"))
		return (exec_unset(args));
	if (!ft_strcmp(args[0], "env"))
		return (exec_env());
	if (!ft_strcmp(args[0], "exit"))
		return (exec_exit(args));
	return (EXIT_FAILURE);
}
