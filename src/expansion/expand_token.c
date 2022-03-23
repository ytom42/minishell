/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:53:23 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/22 21:53:44 by ytomiyos         ###   ########.fr       */
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
		free(now);
		now = tmp;
	}
	*tokens = NULL;
}

void
	remove_quote(t_token *token)
{
	int		i;
	int		state_dq;
	int		state_sq;
	char	*str;

	while (token)
	{
		i = 0;
		state_dq = 0;
		state_sq = 0;
		str = token->str;
		while (str[i])
		{
			if (state_sq && str[i] == '\'')
			{
				ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
				state_sq = 0;
				continue ;
			}
			else if (state_dq && str[i] == '\"')
			{
				ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
				state_dq = 0;
				continue ;
			}
			else if (!state_sq && str[i] == '\"')
			{
				ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
				state_dq = 1;
				continue ;
			}
			else if (!state_dq && str[i] == '\'')
			{
				ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
				state_sq = 1;
				continue ;
			}
			i++;
		}
		token = token->next;
	}
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
		var[EXPAND] = lexer(expanded_str);
		remove_quote(var[EXPAND]);
		free_set((void **)&expanded_str, NULL);
		if (!var[RES])
			var[RES] = var[EXPAND];
		join_token(var[LAST], var[EXPAND]);
		var[LAST] = get_last_token(var[RES]);
		var[NOW] = var[NOW]->next;
	}
	del_tokens(tokens);
	*tokens = var[RES];
}
