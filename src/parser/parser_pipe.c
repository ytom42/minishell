/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:35:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/30 18:59:17 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "execute.h"

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

void	check_nodes(t_node *node, int level)
{
	if (node->type == PIPE && !g_master.error_flag)
	{
		if ((node->left && !node->left->command->args) || \
			(level == 0 && (node->right && !node->right->command->args)))
		{
			print_syntax_error("|");
			g_master.error_flag = TRUE;
		}
	}
	if (node->left)
		check_nodes(node->left, level + 1);
	if (node->right)
		check_nodes(node->right, level + 1);
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
	check_nodes(node_top, 0);
	if (g_master.error_flag)
	{
		del_nodes_list(node_top);
		del_token_list(*token);
		node_top = NULL;
	}
	free(info);
	return (node_top);
}
