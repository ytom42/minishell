/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:36:39 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 19:44:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "libft.h"

extern t_master	g_master;

bool
	is_valid_identifier(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg[i])
		return (FALSE);
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
		return (FALSE);
	while (arg[++i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_environ
	*get_env(char *key)
{
	t_environ	*env;

	if (!g_master.environs || !key)
		return (NULL);
	env = g_master.environs;
	while (env)
	{
		if (ft_strcmp(env->key, (char *)key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char
	*get_cwd_path(char *arg, bool flag)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && flag)
		print_cwd_error(arg);
	return (cwd);
}
