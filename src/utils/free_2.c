/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:22:12 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 17:23:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void
	del_redirects(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	if (redirect->filename)
		del_token_list(redirect->filename);
	if (redirect->heredoc)
		del_token_list(redirect->heredoc->contents);
	free(redirect);
}

static void
	del_commands(t_command *command)
{
	if (command == NULL)
		return ;
	del_token_list(command->args);
	free(command);
}

static void
	del_nodes(t_node *node)
{
	del_commands(node->command);
	del_redirects(node->command->redirects);
	free(node);
}

void
	del_nodes_list(t_node	*node)
{
	t_node	*left_node;
	t_node	*right_node;

	left_node = NULL;
	right_node = NULL;
	if (node == NULL)
		return ;
	if (node->left)
		left_node = node->left;
	if (node->right)
		right_node = node->right;
	del_nodes(node);
	del_nodes_list(left_node);
	del_nodes_list(right_node);
}
