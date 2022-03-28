/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:38:36 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/28 12:07:27 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_delimiter(char c)
{
	int		i;

	i = 0;
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	// else if (c == '\n')
	// 	return (1);
	else if (c == '\0')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '|')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_space(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		*i += 1;
}
