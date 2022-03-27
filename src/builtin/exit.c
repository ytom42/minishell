/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 10:25:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/27 12:41:02 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "libft.h"
#include <errno.h>

#define LONG_LONG_MAX __LONG_LONG_MAX__

extern t_master	g_master;

static unsigned long long
	atounll(char *s)
{
	unsigned long long	res;

	res = 0;
	while (*s == '\t' || *s == '\v' || *s == '\f'
		|| *s == '\r' || *s == '\n' || *s == ' ')
		s++;
	if (*s == '-')
		s++;
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10;
		res += *s - '0';
		s++;
	}
	return (res);
}

static bool
	check_over_under(char *args)
{
	unsigned long long	tmp;
	unsigned long long	check;
	bool				sign;
	

	sign = FALSE;
	if (str_is_sign(args))
		sign = TRUE;
	if (sign)
	{
		check = LONG_LONG_MAX;
		check++;
	}
	else
		check = LONG_LONG_MAX;
	tmp = atounll(args);
	if (tmp > check)
		return (TRUE);
	return (FALSE);
}

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
	int		status;
	int		i;
	bool	err_flag;

	i = 1;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (!args[i])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_master.exit_cd);
	}
	errno = 0;
	err_flag = check_over_under(args[i]);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (err_flag)
	{
		print_num_arg_error(args[i]);
		exit(255);
	}
	status = ft_atoi(args[i]);
	if (!found_error(args, i))
		exit(status);
	return (EXIT_FAILURE);
}
