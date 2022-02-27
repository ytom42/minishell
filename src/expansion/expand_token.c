/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:53:23 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 12:57:42 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execute.h"
#include "utils.h"

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
		free(now);
		now = tmp;
	}
	*tokens = NULL;
}

void
	expand_tokens(t_token **tokens)
{
	char	*expanded_str;
	t_token	*var[4];

	if (!tokens || !*tokens)
		return ;
	var[RES] = NULL;
	var[LAST] = NULL;
	var[NOW] = *tokens;
	while (var[NOW])
	{
		expanded_str = expand_env_var(var[NOW]->str);
		var[EXPAND] = tokenise(expanded_str, TRUE);
		free_set((void **)&expanded_str, NULL);
		if (!var[RES])
			var[RES] == var[EXPAND];
		join_token(var[LAST], var[EXPAND]);
		var[LAST] = get_last_token(var[RES]);
		var[NOW] = var[NOW]->next;
	}
	del_tokens(tokens);
	*tokens = var[RES];
}
