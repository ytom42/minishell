/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:01:49 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 14:14:25 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void
	del_redirects(t_redirect *redirect)
{
	t_redirect	*tmp;

	if (redirect == NULL)
		return ;
	while (redirect)
	{
		tmp = redirect;
		redirect = redirect->next;
		if (tmp->filename)
			del_token(tmp->filename);
		if (tmp->heredoc)
			del_token_list(tmp->heredoc->contents);
		free_set((void **)&tmp, NULL);
	}
}

static void
	del_commands(t_command *command)
{
	if (command == NULL)
		return ;
	del_token_list(command->args);
	del_redirects(command->redirects);
	free_set((void **)&command, NULL);
}

static void
	del_nodes(t_node *node)
{
	del_commands(node->command);
	free_set((void **)&node, NULL);
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
