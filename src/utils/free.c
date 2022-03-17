/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:45:06 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/17 16:37:11 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void
	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

void
	instant_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void
	del_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

static void
	del_redirects(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	free(redirect->filename);
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
	del_nodes(t_node	*node)
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
