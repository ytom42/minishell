/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:34:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:56:49 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	add_redirect(t_node *node, t_token **token, t_redirect **prev)
{
	t_redirect	*new;
	t_redirect	*tmp;
	t_token		*free_tmp;

	new = redirect_new(token);
	free_tmp = *token;
	*token = (*token)->next;
	del_token(free_tmp);
	if (!(*token) || (*token)->type != WORD)
		return ;
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
	new->prev = *prev;
	*prev = new;
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

t_node	*get_command_node(t_token **token, t_parse_info *info)
{
	t_node		*node;
	t_redirect	*prev;

	node = node_new(NODE_COMMAND);
	prev = NULL;
	while ((*token) && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD)
			add_command(node, token);
		else
			add_redirect(node, token, &prev);
	}
	if (info->prev_command)
		info->prev_command->next = node->command;
	info->prev_command = node->command;
	return (node);
}
