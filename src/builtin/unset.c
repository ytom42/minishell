/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:50:58 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/03 12:20:34 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "utils.h"
#include "libft.h"

extern t_master	g_master;

void
	del_env(t_environ **head, char *target)
{
	t_environ	*tmp;
	t_environ	*prev;

	if (!head || !*head || !target)
		return ;
	prev = NULL;
	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, target))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*head = tmp->next;
			free_set((void **)&tmp->key, NULL);
			free_set((void **)&tmp->value, NULL);
			free_set((void **)&tmp, NULL);
			tmp = NULL;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int
	exec_unset(char **args)
{
	size_t			i;
	int				res;

	res = EXIT_SUCCESS;
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_identifier_error("unset", args[i]);
			res = EXIT_FAILURE;
		}
		else
		{
			del_env(&g_master.environs, args[i]);
		}
	}
	return (res);
}
