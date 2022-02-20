/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/20 09:46:24 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"
#include "execute.h"

extern t_master	master;

void
	**split_key_value(char *arg, char *sep, char *value, bool add_request)
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
		if (!replace_dup_env(key, new_value))
			if (!append_env(&master.environs,
				new_env(ft_strdup(key), ft_strdup(new_value))))
				error_exit(NULL);
	}
}

bool
	replace_dup_env(char *key, char *value)
{
	t_environ	*env;

	env = master.environs;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (!is_declear)
			{
				free(env->value);
				env->value = ft_strdup(value);
				env->is_delear = is_declear;
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
