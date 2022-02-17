/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:17:57 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 16:51:13 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static t_bool
	is_valid_opt(char *opt)
{
	size_t	i;

	i = 0;
	while (opt[++i])
		if (opt[i] != 'n')
			return (FALSE);
	return (TRUE);
}

int
	exec_echo(char **args)
{
	size_t	i;
	t_bool is_opt;

	i = 1;
	if (args[i] && args[i][0] == '-')
		is_opt = is_valid_opt(args[i]);
	else
		is_opt = FALSE;
	if (is_opt)
		i++;
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
