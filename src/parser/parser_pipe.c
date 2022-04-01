/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:35:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/04/01 18:00:31 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

extern t_master	g_master;

t_node	*get_pipe_node(t_token **token, t_node *left_node, t_parse_info *info)
{
	t_node	*node;
	t_node	*right_node;
	t_token	*tmp;

	node = node_new(NODE_PIPE);
	tmp = *token;
	(*token) = (*token)->next;
	right_node = get_command_node(token, info);
	node->left = left_node;
	node->right = right_node;
	del_token(tmp);
	return (node);
}

t_node	*loop_pipe(t_token **token)
{
	t_node			*node_top;
	t_parse_info	*info;

	info = (t_parse_info *)malloc(sizeof(t_parse_info));
	info->prev_command = NULL;
	node_top = get_command_node(token, info);
	while (*token && (*token)->type == PIPE)
		node_top = get_pipe_node(token, node_top, info);
	if (g_master.error_flag)
	{
		del_nodes_list(node_top);
		del_token_list(*token);
		node_top = NULL;
	}
	free_set((void **)&info, NULL);
	return (node_top);
}
