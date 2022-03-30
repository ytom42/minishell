/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:45:06 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/30 21:19:57 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

extern t_master	g_master;

void
	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

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
	del_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free_set((void **)&token->str, NULL);
	free_set((void **)&token, NULL);
}

void
	*del_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		del_token(tmp);
	}
	return (NULL);
}

void
	del_tmp_env(t_environ *envs)
{
	t_environ	*tmp;

	while (envs)
	{
		free(envs->key);
		free(envs->value);
		tmp = envs->next;
		free(envs);
		envs = tmp;
	}
	g_master.tmp_env = NULL;
}
