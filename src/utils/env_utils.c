/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:08:52 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/03 12:04:33 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "execute.h"
#include "builtin.h"

extern t_master	g_master;

t_environ
	*dup_env(t_environ *env)
{
	t_environ *tmp;

	tmp = (t_environ *)malloc(sizeof(t_environ));
	if (!tmp)
		return (NULL);
	tmp->key = env->key;
	tmp->value = env->value;
	tmp->next = NULL;
	return (tmp);
}

t_environ
	*dup_envs(t_environ *env)
{
	t_environ *list;
	t_environ *tmp;

	list = NULL;
	while (env)
	{
		tmp = dup_env(env);
		if (append_env(&(list), tmp))
		{
			free_set((void **)&tmp, NULL);
			free_set((void **)&list, NULL);
			return (NULL);
		}
		env = env->next;
	}
	return (list);
}

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
