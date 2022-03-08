/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:30:12 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/08 19:11:07 by ytomiyos         ###   ########.fr       */
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
			if (token) printf(", ");
		}
		printf("\n%s", END);
}

void	print_redirect(t_node *node)
{
	t_redirect *redirect;
	redirect = node->command->redirects;
	printf("redirect  : ");
	char **type = (char *[]){"<", ">", ">>", "<<"};
	if (!redirect)
		printf("%sNULL%s", CYAN, END);
	while (redirect)
	{
		printf("%s[%s%s%s]", type[redirect->type], CYAN, redirect->filename->str, END);
		redirect = redirect->next;
		if (redirect) printf(", ");
	}
	printf("\n");
}

void	print_node(t_node *node)
{
	printf("%s== %s ==\n%s", MAGENTA, node->type == NODE_COMMAND ? "COMMAND" : "PIPE", END);
	printf("node_ptr  :%s%p%s\n", RED, node, END);
	if (node->type == NODE_COMMAND)
	{
		print_command(node);
		print_redirect(node);
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
	printf("%s%s========== print_node ==========\n%s", YELLOW, BOLD, END);
	print_node(node);
	printf("%s%s================================\n%s", YELLOW, BOLD, END);
}