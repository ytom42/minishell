/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 10:25:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/07 14:23:18 by ytomiyos         ###   ########.fr       */
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
	over_ull(char *str)
{
	int					i;
	int					len;
	unsigned long long	ans;

	if (str == NULL)
		return (FALSE);
	len = ft_strlen(str);
	if (len > 20)
		return (TRUE);
	else if (len == 20)
	{
		ans = 0;
		i = 1;
		while (str[i])
			ans = (ans * 10) + (str[i++] - '0');
		if (str[0] > '1' || (str[0] == '1' && ans > 8446744073709551615))
			return (TRUE);
	}
	return (FALSE);
}

static bool
	check_over_under(char *args)
{
	unsigned long long	tmp;
	unsigned long long	check;
	bool				sign;

	sign = FALSE;
	if (over_ull(args))
		return (TRUE);
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
