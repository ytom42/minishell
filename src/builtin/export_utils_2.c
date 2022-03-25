/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:49:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 16:56:10 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"
#include "execute.h"

extern t_master	g_master;

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

t_environ
	*add_env(t_environ *list, t_environ *new)
{
	t_environ	*ret_list;
	t_environ	*prev;

	if (list == NULL)
		return (new);
	ret_list = list;
	prev = NULL;
	while (list)
	{
		if (ft_strcmp(list->key, new->key) >= 0)
		{
			new->next = list;
			if (prev)
				prev->next = new;
			else
				return (new);
			return (ret_list);
		}
		prev = list;
		list = list->next;
	}
	prev->next = new;
	return (ret_list);
}

void
	sort_envs(t_environ **env)
{
	t_environ	*new;
	t_environ	*list;

	list = NULL;
	while (*env)
	{
		new = *env;
		*env = (*env)->next;
		new->next = NULL;
		list = add_env(list, new);
	}
	*env = list;
}
