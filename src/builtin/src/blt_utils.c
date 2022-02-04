/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:33:04 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/12 10:05:36 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void
	instant_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void
	release_target(t_environ *target)
{
	free(target->value);
	target->value = NULL;
}

t_environ
	*search_key(t_environ *env, char *target)
{
	t_environ	*key_pos;

	key_pos = env;
	while (key_pos)
	{
		if (ft_strcmp(key_pos->key, target) == 0)
			break ;
		key_pos = key_pos->next;
	}
	return (NULL);
}

void
	replace_env_value(t_environ *env, char *new_value)
{
	if (!env)
		return ;
	free(env->value);
	env->value = ft_strdup(new_value);
}
