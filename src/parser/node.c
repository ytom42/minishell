/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:39:15 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/25 18:35:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

t_node	*node_new(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->command = (t_command *)malloc(sizeof(t_command));
	if (node->command == NULL)
		return (del_nodes_list(node), NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->command->args = NULL;
	node->command->redirects = NULL;
	node->command->pid = -1;
	node->command->next = NULL;
	return (node);
}

static void	redirect_init(t_redirect *redirect)
{
	redirect->fd_io = -1;
	redirect->fd_file = -1;
	redirect->fd_backup = -1;
	redirect->filename = NULL;
	redirect->prev = NULL;
	redirect->next = NULL;
	redirect->heredoc = NULL;
}

t_redirect	*redirect_new(t_token **token)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect_init(redirect);
	if ((*token)->type == LESSER)
	{
		redirect->type = REDIR_INPUT;
		redirect->fd_io = STDIN_FILENO;
	}
	else if ((*token)->type == D_LESSER)
		redirect->type = REDIR_HEREDOC;
	else if ((*token)->type == GREATER)
	{
		redirect->type = REDIR_OUTPUT;
		redirect->fd_io = STDOUT_FILENO;
	}
	else if ((*token)->type == D_GREATER)
	{
		redirect->type = REDIR_APPEND_OUTPUT;
		redirect->fd_io = STDOUT_FILENO;
	}
	return (redirect);
}
