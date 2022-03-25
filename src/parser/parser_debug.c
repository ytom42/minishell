/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:30:12 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/25 17:16:41 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_command(t_node *node)
{
	t_token		*token;

	token = node->command->args;
	printf("command   : %s%s", CYAN, BOLD);
	while (token)
	{
		printf("%s", token->str);
		token = token->next;
		if (token)
			printf(", ");
	}
	printf("\n%s", END);
}

void	print_next_command(t_node *node)
{
	t_token	*token;

	if (node->command->next == NULL)
	{
		printf("next_command: NULL\n");
		return ;
	}
	token = node->command->next->args;
	printf("next_command: ");
	printf("%s%s", CYAN, BOLD);
	while (token)
	{
		printf("%s", token->str);
		token = token->next;
		if (token)
			printf(", ");
	}
	printf("%s", END);
	printf("\n");
}

void	print_redirect(t_node *node)
{
	t_redirect	*redirect;
	char **type = (char *[]){"<", ">", ">>", "<<"};

	redirect = node->command->redirects;
	printf("redirect  : ");
	if (!redirect)
		printf("%sNULL%s", CYAN, END);
	while (redirect)
	{
		if (redirect)
		{
			printf("%s", type[redirect->type]);
			if (redirect->filename)
				printf("[%s%s%s]", CYAN, redirect->filename->str, END);
			else
				printf("[%sNULL%s]", CYAN, END);
		}
		if (redirect->prev && redirect->filename)
			printf("[%s]", redirect->prev->filename->str);
		redirect = redirect->next;
		if (redirect)
			printf(", ");
	}
	printf("\n");
}

void	print_node(t_node *node)
{
	printf("%s== %s ==\n%s", MAGENTA, \
		node->type == NODE_COMMAND ? "COMMAND" : "PIPE", END);
	printf("node_ptr  :%s%p%s\n", RED, node, END);
	if (node->type == NODE_COMMAND)
	{
		print_command(node);
		print_redirect(node);
		print_next_command(node);
	}
	else
	{
		printf("node_left :%p\n", node->left);
		printf("node_right:%p\n", node->right);
	}
	if (node->left)
		print_node(node->left);
	if (node->right)
		print_node(node->right);
}

void	print_nodes(t_node *node)
{
	if (node == NULL)
	{
		printf("debugger: node is NULL\n");
		return ;
	}
	printf("%s%s========== print_node ==========\n%s", YELLOW, BOLD, END);
	print_node(node);
	printf("%s%s================================\n%s", YELLOW, BOLD, END);
	fflush(stdout);
}
