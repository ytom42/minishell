/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 08:56:01 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"

extern t_master	master;

char
	**split_key_value(char *arg)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * 3);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == 0)
	{
		free(split);
		return (NULL);
	}
	split[0] = ft_strndup(arg, i);
	if (ft_strlen(arg) != ft_strlen(split[0]))
		split[1] = ft_strdup(arg + i + 1);
	else
		split[1] = NULL;
	split[2] = NULL;
	return (split);
}

void
	update_env(char **args)
{
	// // keyがpwdだった場合
	// if (!ft_strcmp(split[0], "PWD"))
	// 	add_declear_pwd(split, "PWD");
	// // keyがoldpwdだった場合
	// else if (!ft_strcmp(split[0], "OLDPWD") && master.oldpwd)
	// 	add_declear_pwd(split, "OLD");
	// valueの置き換え
	if (!replace_dup_env(split[0], split[1]))
		append_env(&master.environs,
			new_env(ft_strdup(split[0]), ft_strdup(split[1])));
}

t_bool
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
