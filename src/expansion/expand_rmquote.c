/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_rmquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:17:26 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/25 22:29:20 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void
	loop_token(char *str)
{
	int		i;
	int		state_dq;
	int		state_sq;

	i = 0;
	state_dq = 0;
	state_sq = 0;
	while (str[i])
	{
		if (state_sq && str[i] == '\'')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			state_sq = 0;
		}
		else if (state_dq && str[i] == '\"')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			state_dq = 0;
		}
		else if (!state_sq && str[i] == '\"')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			state_dq = 1;
		}
		else if (!state_dq && str[i] == '\'')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			state_sq = 1;
		}
		else
			i++;
	}
}

void
	remove_quote(t_token *token)
{
	while (token)
	{
		loop_token(token->str);
		token = token->next;
	}
}
