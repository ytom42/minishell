/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:45:06 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 18:14:40 by kfumiya          ###   ########.fr       */
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
	del_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free_set((void **)&token->str, NULL);
	free_set((void **)&token, NULL);
}

void
	*del_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		del_token(tmp);
	}
	return (NULL);
}

static void
	del_redirects(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	if (redirect->filename)
		del_token_list(redirect->filename);
	if (redirect->heredoc)
		del_token_list(redirect->heredoc->contents);
	free_set((void **)&redirect, NULL);
}

static void
	del_commands(t_command *command)
{
	if (command == NULL)
		return ;
	del_token_list(command->args);
	free_set((void **)&command, NULL);
}

static void
	del_nodes(t_node *node)
{
	del_commands(node->command);
	del_redirects(node->command->redirects);
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

void
	del_tmp_env(t_environ **envs)
{
	t_environ	*tmp;

	while (*envs)
	{
		free((*envs)->key);
		free((*envs)->value);
		tmp = (*envs)->next;
		free(*envs);
		*envs = tmp;
	}
}
