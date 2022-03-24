/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:05:14 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansion.h"

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
	return (token_list);
}
