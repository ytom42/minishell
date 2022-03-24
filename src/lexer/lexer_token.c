/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:04:54 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:05:22 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansion.h"

static int	gl_size(char *line, int i)
{
	int		size;

	size = 1;
	if (line[i] == '>' && line[i + 1] == '>')
		size += 1;
	else if (line[i] == '<' && line[i + 1] == '<')
		size += 1;
	return (size);
}

static int	quote_size(char *line, int i)
{
	int	size;
	int	sq;
	int	dq;

	size = 0;
	sq = 0;
	dq = 0;
	if (line[i + size] == '\"')
		dq = 1;
	else if (line[i + size] == '\'')
		sq = 1;
	size = 1;
	while (line[i + size])
	{
		if ((dq && line[i + size] == '\"') || (sq && line[i + size] == '\''))
		{
			size += 1;
			break ;
		}
		size += 1;
	}
	return (size);
}

static int	general_size(char *line, int i)
{
	int		size;
	char	c;

	size = 0;
	while (line[i + size])
	{
		c = line[i + size];
		if (c == '\"' || c == '\'')
			size += quote_size(line, i + size);
		else if (is_delimiter(c))
			break ;
		else
			size += 1;
	}
	return (size);
}

static int	get_token_size(char *line, int i)
{
	if (line[i] == '>' || line[i] == '<')
		return (gl_size(line, i));
	else if (line[i] == '|')
		return (1);
	else
		return (general_size(line, i));
}

t_token	*get_token(char *line, int *i)
{
	int		size;
	char	*str;
	t_token	*new_token;

	size = 0;
	skip_space(line, i);
	size = get_token_size(line, *i);
	if (size == 0)
		return (NULL);
	str = ft_substr(&line[*i], 0, size);
	new_token = token_lstnew(str);
	*i += size;
	return (new_token);
}
