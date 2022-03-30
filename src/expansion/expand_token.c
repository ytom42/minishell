/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:53:23 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/30 15:50:27 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execute.h"
#include "utils.h"
#include "lexer.h"

#define NOW 0
#define LAST 1
#define EXPAND 2
#define RES 3

void
	join_token(t_token *dest, t_token *src)
{
	if (!dest || !src || dest == src)
		return ;
	dest->next = src;
	src->prev = dest;
}

t_token
	*get_last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}

void
	del_tokens(t_token **tokens)
{
	t_token	*now;
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	now = *tokens;
	while (now)
	{
		tmp = now->next;
		free_set((void **)&now, NULL);
		now = tmp;
	}
	*tokens = NULL;
}

static void
	reset_token(t_token **var, char *expanded_str, int is_heredoc)
{
	if (is_heredoc)
		var[EXPAND] = token_lstnew(expanded_str);
	else
	{
		var[EXPAND] = lexer(expanded_str);
		remove_quote(var[EXPAND]);
		free_set((void **)&expanded_str, NULL);
	}
}

void
	expand_tokens(t_token **tokens, int is_heredoc)
{
	char	*expanded_str;
	t_token	*var[4];
	int		index;

	if (!tokens || !*tokens)
		return ;
	var[RES] = NULL;
	var[LAST] = NULL;
	var[NOW] = *tokens;
	index = 0;
	while (var[NOW])
	{
		expanded_str = expand_env_var(var[NOW]->str, index, is_heredoc);
		reset_token(var, expanded_str, is_heredoc);
		if (!var[RES])
			var[RES] = var[EXPAND];
		join_token(var[LAST], var[EXPAND]);
		var[LAST] = get_last_token(var[RES]);
		var[NOW] = var[NOW]->next;
		index += 1;
	}
	del_tokens(tokens);
	*tokens = var[RES];
}
