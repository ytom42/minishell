/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:43:40 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:07:23 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_type_str(char c)
{
	if (c == WORD)
		return ("WORD");
	else if (c == PIPE)
		return ("PIPE");
	else if (c == LESSER)
		return ("LESSER");
	else if (c == D_LESSER)
		return ("D_LESSER");
	else if (c == GREATER)
		return ("GREATER");
	else if (c == D_GREATER)
		return ("D_GREATER");
	else
		return ("UNKNOWN");
}

void	print_token(t_token *lst)
{
	int	i;

	if (lst == NULL)
	{
		printf("token_list is NULL\n");
		return ;
	}
	printf("%s%s========= print_token  =========\n%s", YELLOW, BOLD, END);
	i = 1;
	while (lst)
	{
		printf("%02d:%s [%s]\n", i, lst->str, get_type_str(lst->type));
		lst = lst->next;
		i++;
	}
	printf("%s%s================================\n%s", YELLOW, BOLD, END);
	fflush(stdout);
}
