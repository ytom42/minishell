/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:36:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/03 11:23:22 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "libft.h"

t_environ
	*new_env(char *key, char *value)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	// new->prev = NULL;
	new->next = NULL;
	return (new);
}

bool
	append_env(t_environ **envs, t_environ *new)
{
	t_environ	*tmp;

	if (!new || !envs)
		return (FALSE);
	if (!*envs)
	{
		*envs = new;
		return (TRUE);
	}
	tmp = *envs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (TRUE);
}
