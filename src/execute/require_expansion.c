/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   require_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:34:46 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/19 20:54:15 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"

static size_t
	token_lstsize(t_token *token)
{
	size_t	size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

static char
	**replace_args(t_command *cmd)
{
	char	**args;
	t_token	*now;
	size_t	size;
	size_t	i;

	size = token_lstsize(cmd->args);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		error_exit(NULL);
	i = 0;
	now = cmd->args;
	while (now)
	{
		args[i] = ft_strdup(now->str);
		if (!args[i])
			error_exit(NULL);
		now = now->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

bool
	require_expansion(t_command *cmd, char ***args)
{
	expand_tokens(&cmd->args);
	*args = replace_args(cmd);
	if (!*args[0])
		return (FALSE);
	return (TRUE);
}
