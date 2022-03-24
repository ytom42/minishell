/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:17:57 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/23 23:03:18 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static bool
	is_valid_opt(char *opt)
{
	size_t	i;

	i = 0;
	while (opt[++i])
		if (opt[i] != 'n')
			return (FALSE);
	return (TRUE);
}

static size_t
	skip_opt(char **args)
{
	size_t	i;

	i = 1;
	while (42)
	{
		if (args[i] && args[i][0] == '-' && args[i][1])
		{
			if (!is_valid_opt(args[i]))
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int
	exec_echo(char **args)
{
	size_t	i;
	bool	is_opt;

	i = skip_opt(args);
	if (i > 1)
		is_opt = TRUE;
	while (args[i])
	{
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (is_opt == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
