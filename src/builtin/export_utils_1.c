/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/01 17:59:42 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"
#include "execute.h"

extern t_master	g_master;

void
	split_key_value(char *arg, char **sep, char **value, bool *add_request)
{
	*sep = ft_strchr(arg, '=');
	if (*sep)
	{
		**sep = '\0';
		if (*sep != arg && *(*sep - 1) == '+')
		{
			*(*sep - 1) = '\0';
			*add_request = TRUE;
		}
		if (*sep)
			*value = *sep + 1;
	}
	else
		*value = NULL;
}

void
	update_env(char *key, char *new_value, bool add_request, bool is_exp)
{
	char		*old_value;
	t_environ	*env;

	env = get_env(key);
	old_value = NULL;
	if (env)
		old_value = env->value;
	if (add_request && old_value)
	{
		if (old_value || new_value)
		{
			env->value = ft_strjoin(old_value, new_value);
			free_set((void **)&old_value, NULL);
			if (!env->value)
				error_exit(NULL);
		}
	}
	else
	{
		if (!replace_dup_env(key, new_value, FALSE))
			if (!append_env(&g_master.environs, new_env(key, new_value)))
				error_exit(NULL);
	}
	if (!is_exp)
		free_set((void **)&new_value, NULL);
}

bool
	replace_dup_env(char *key, char *value, bool is_env)
{
	t_environ	*env;

	env = g_master.environs;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (!is_env)
			{
				free_set((void **)&env->value, NULL);
				env->value = ft_strdup(value);
				env->is_env = is_env;
			}
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

void
	restore_arg(char *sep, bool add_request)
{
	if (sep)
	{
		*sep = '=';
		if (add_request)
			*(sep - 1) = '+';
	}
}

int
	envs_size(t_environ *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
