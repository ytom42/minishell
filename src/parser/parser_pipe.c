/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:35:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/17 20:35:34 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*get_pipe_node(t_token **token, t_node *left_node, t_parse_info *info)
{
	t_node	*node;
	t_node	*right_node;

	node = node_new(NODE_PIPE);
	(*token) = (*token)->next;
	right_node = get_command_node(token, info);
	node->left = left_node;
	node->right = right_node;
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
	{
		node_top = get_pipe_node(token, node_top, info);
	}
	free(info);
	return (node_top);
}
