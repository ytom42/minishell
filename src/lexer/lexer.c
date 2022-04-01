/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/04/01 16:01:33 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansion.h"
#include "execute.h"

t_master	g_master;

void	check_tokenlist(t_token *list)
{
	t_token		*prev;
	t_token		*now;

	prev = NULL;
	now = list;
	while (now)
	{
		if (!prev && now->type == PIPE)
			g_master.error_flag = TRUE;
		else if (prev && prev->type == PIPE && now->type == PIPE)
			g_master.error_flag = TRUE;
		else if (now->type == PIPE && !now->next)
			g_master.error_flag = TRUE;
		prev = now;
		now = now->next;
	}
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*token_list;
	t_token	*new_token;

	if (!line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		new_token = get_token(line, &i);
		token_list = token_lstaddback(token_list, new_token);
		skip_space(line, &i);
	}
	check_tokenlist(token_list);
	if (g_master.error_flag)
	{
		print_syntax_error("|");
		del_token_list(token_list);
		token_list = NULL;
	}
	return (token_list);
}
