/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:49:03 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 19:50:57 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "expansion.h"

extern t_master	g_master;

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
