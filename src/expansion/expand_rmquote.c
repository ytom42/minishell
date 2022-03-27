/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_rmquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:17:26 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/27 15:54:21 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void
	loop_token_rmquote(char *str, int state_dq, int state_sq)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (state_sq && str[i] == '\'')
			state_sq = 0;
		else if (state_dq && str[i] == '\"')
			state_dq = 0;
		else if (!state_sq && str[i] == '\"')
			state_dq = 1;
		else if (!state_dq && str[i] == '\'')
			state_sq = 1;
		else
		{
			i++;
			continue ;
		}
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
	}
}

void
	remove_quote(t_token *token)
{
	while (token)
	{
		loop_token_rmquote(token->str, 0, 0);
		token = token->next;
	}
}
