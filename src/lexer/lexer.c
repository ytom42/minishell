/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/19 18:15:16 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

typedef struct	s_token_checker
{
	int		len;
	bool	dq;
	bool	sq;
}				t_token_checker;

static int		gl_size(char *line, int *i)
{
	int		size;

	size = 1;
	if (line[*i] == '>' && line[*i + 1] == '>')
		size += 1;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		size += 1;
	return (size);
}

static int		quote_size(char *line, int *i)
{
	int	size;
	// int dq;
	// int sq;

	size = 0;
	// if (line[*i] == '"')
	// {
	// 	dq = 1;
	// 	size += 1;
	// }
	// else if (line[*i] == '\'')
	// {
	// 	sq = 1;
	// 	size += 1;
	// }
	while (line[*i + size])
	{
		if (is_delimiter(line[*i + size]))
			break ;
		// if (dq && line[*i + size] == '"')
		// {
		// 	size++;
		// 	dq = 0;
		// 	// break ;
		// }
		// if (sq && line[*i + size] == '\'')
		// {
		// 	size++;
		// 	sq = 0;
		// 	// break ;
		// }
		size += 1;
	}
	return (size);
}

int get_token_size(char *line, int *i)
{
	if (line[*i] == '>' || line[*i] == '<')
		return (gl_size(line, i));
	else if (line[*i] == '|')
		return (1);
	else
		return (quote_size(line, i));
}

t_token	*get_token(char *line, int *i)
{
	int		size;
	char	*str;
	t_token	*new_token;

	size = 0;
	skip_space(line, i);
	size = get_token_size(line, i);
	if (size == 0)
		return (NULL);
	str = ft_substr(&line[*i], 0, size);
	new_token = token_lstnew(str);
	*i += size;
	return (new_token);
}

t_token *lexer(char *line)
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
		if (new_token == NULL)
			break ;
		token_list = token_lstaddback(token_list, new_token);
	}
	return (token_list);
}
