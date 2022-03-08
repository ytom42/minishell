/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:35:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/08 17:42:32 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*get_pipe_node(t_token **token, t_node *left_node)
{
	t_node	*node;
	t_node	*right_node;

	node = node_new(NODE_PIPE);
	(*token) = (*token)->next;
	right_node = get_command_node(token);
	node->left = left_node;
	node->right = right_node;
	return (node);
}

t_node	*loop_pipe(t_token **token)
{
	t_node	*node_top;

	node_top = get_command_node(token);
	while (*token && (*token)->type == PIPE)
	{
		node_top = get_pipe_node(token, node_top);
	}
	return (node_top);
}
