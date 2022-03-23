/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/23 15:58:26 by kfumiya          ###   ########.fr       */
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
	update_env(char *key, char *new_value, bool add_request)
{
	char		*old_value;
	t_environ	*env;

	env = get_env(key);
	if (env)	
		old_value = env->value;
	if (add_request)
	{
		if (old_value || new_value)
		{
			env->value = ft_strjoin(old_value, new_value);
			if (!env->value)
				error_exit(NULL);
		}
		else
			env->value = NULL;
	}
	else
	{
		if (!replace_dup_env(key, new_value, FALSE))
			if (!append_env(&g_master.environs,
					new_env(key, new_value)))
				error_exit(NULL);
	}
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
				free(env->value);
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
