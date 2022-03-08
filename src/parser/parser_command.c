/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:34:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/08 18:15:15 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_redirect(t_node *node, t_token **token)
{
	t_redirect	*new;
	t_redirect	*tmp;

	new = redirect_new(token);
	*token = (*token)->next;
	if (!(*token) || (*token)->type != WORD)
		return ; //error
	new->filename = *token;
	if (node->command->redirects)
	{
		tmp = node->command->redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		node->command->redirects = new;
	*token = (*token)->next;
}

void	add_command(t_node *node, t_token **token)
{
	t_token		*new;
	t_token		*tmp;

	new = *token;
	*token = (*token)->next;
	if (node->command->args)
	{
		tmp = node->command->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		node->command->args = new;
	new->next = NULL;
}

t_node	*get_command_node(t_token **token)
{
	t_node	*node;

	node = node_new(NODE_COMMAND);
	while ((*token) && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD)
			add_command(node, token);
		else
			add_redirect(node, token);
	}
	return (node);
}
