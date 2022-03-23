/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 10:25:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/22 18:28:48 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "libft.h"
#include <errno.h>

extern t_master	g_master;

static bool
	found_error(char **args, int i)
{
	if (errno || !str_is_digit(args[i]))
	{
		print_num_arg_error(args[i]);
		exit(255);
	}
	i++;
	if (args[i])
	{
		print_error_msg("too many argumets", "exit");
		return (TRUE);
	}
	return (FALSE);
}

int
	exec_exit(char **args)
{
	int	status;
	int	i;

	i = 1;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (!args[i])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_master.exit_cd);
	}
	errno = 0;
	status = ft_atoi(args[i]);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!found_error(args, i))
		exit(status);
	return (EXIT_FAILURE);
}
