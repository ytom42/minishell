/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:33:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/01 17:56:55 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execute.h"

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

char
	*close_dqoute_value(char *str)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin("\"", str);
	free_set((void **)&str, NULL);
	tmp = res;
	res = ft_strjoin(res, "\"");
	free_set((void **)&tmp, NULL);
	return (res);
}

void
	expander_init(t_expander *exper, char *str, int index)
{
	if (!str)
		exper->str = NULL;
	else
	{
		exper->str = ft_strdup(str);
		if (exper->str == NULL)
			error_exit(NULL);
	}
	exper->index = 0;
	exper->arg_index = index;
	exper->state = STATE_GENERAL;
}
