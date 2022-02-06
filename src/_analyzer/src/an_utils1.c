/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:22:51 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/10 05:30:40 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

bool
	is_white(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

void
	skip_white(char *line)
{
	while (is_white(*line))
		(*line)++;
}

bool
	is_delimiter(int c)
{
	return (ft_in_set(c, DELIMITERS));
}

bool
	is_quote(char c)
{
	return (c == SGL_QT || c == DBL_QT);
}

bool
	search_close_quote(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	while (line[++*i])
		if (line[*i] == quote)
			return (true);
	return (false);
}
