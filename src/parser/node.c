/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:39:15 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/17 20:16:10 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*node_new(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->command = (t_command *)malloc(sizeof(t_command));
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->command->args = NULL;
	node->command->redirects = NULL;
	node->command->pid = -1;
	node->command->next = NULL;
	return (node);
}

t_redirect	*redirect_new(t_token **token)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	redirect->fd_io = -1;
	redirect->fd_file = -1;
	redirect->fd_backup = -1;
	redirect->prev = NULL;
	redirect->next = NULL;
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
