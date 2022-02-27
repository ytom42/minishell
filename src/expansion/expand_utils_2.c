/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:33:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 11:28:50 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

t_token_type
	get_token_type(char c)
{
	const char	commands[] = {
		'|', '\'', '\"', ' ', ';', '\\', '>', '<', '\t', '\0'};
	int			i;

	i = 10;
	while (i--)
	{
		if (commands[i] == c)
			return (commands[i]);
	}
	return (CHAR_GENERAL);
}

t_token_state
	get_token_state(t_token_state state, t_token_type type)
{
	if (state == STATE_GENERAL)
	{
		if (type == CHAR_QOUTE)
			return (STATE_IN_QUOTE);
		if (type == CHAR_DQUOTE)
			return (STATE_IN_DQUOTE);
	}
	else if (state == STATE_IN_QUOTE && type != CHAR_QOUTE)
		return (STATE_IN_QUOTE);
	else if (state == STATE_IN_DQUOTE && type != CHAR_DQUOTE)
		return (STATE_IN_DQUOTE);
	return (STATE_GENERAL);
}
