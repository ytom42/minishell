/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:34:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/25 18:28:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "execute.h"

extern t_master	g_master;

void	add_redirect(t_node *node, t_token **token, t_redirect **prev)
{
	t_redirect	*new;
	t_redirect	*tmp;
	t_token		*free_tmp;

	new = redirect_new(token);
	free_tmp = *token;
	*token = (*token)->next;
	del_token(free_tmp);
	if (!(*token) && g_master.error_flag == FALSE)
	{
		print_syntax_error("newline");
		g_master.error_flag = TRUE;
	}
	else if ((*token)->type != WORD && g_master.error_flag == FALSE)
	{
		print_syntax_error((*token)->str);
		g_master.error_flag = TRUE;
	}
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
	if (*token)
		*token = (*token)->next;
	new->filename->next = NULL;
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
	if (node == NULL)
		return (NULL);
	prev = NULL;
	while ((*token) && (*token)->type != PIPE && g_master.error_flag == FALSE)
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
