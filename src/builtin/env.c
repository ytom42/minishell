/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:17:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 17:10:00 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

extern t_master	g_master;

static void
	print_env(t_environ *env)
{
	if (env->value == NULL)
		return ;
	ft_putstr_fd(env->key, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(env->value, STDOUT_FILENO);
}

int
	exec_env(void)
{
	t_environ *env;

	env = g_master.environs;
	while (env)
	{
		print_env(env);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
