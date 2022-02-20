/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilutin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:36:39 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/19 18:38:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executo.h"
#include "libft.h"

extern t_master g_master;

char
	*get_env_value(char *key)
{
	t_environ *env;

	if (!key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa(g_master.exit_cd));
	env = g_master.environs;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

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
	*get_cwd_path(char *arg)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		print_cwd_error(arg);
	return (cwd);
}
