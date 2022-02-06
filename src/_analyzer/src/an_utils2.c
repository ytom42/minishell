/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:34:32 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/10 05:27:37 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

bool
	is_redirect(char c)
{
	return (c == R_RDRCT || c == L_RDRCT);
}

bool
	is_double_redirect(char *line)
{
	if (is_redirect(line[0]))
		if (line[0] == line[1])
			return (true);
	return (false);
}

bool
	is_type_pipe(t_token *token)
{
	return (token->type == TYPE_PIPE);
}

bool
	check_close_quote(t_token *token)
{
	int		i;
	bool	close;
	char	*tmp;

	close = true;
	tmp = token->token;
	i = -1;
	while (tmp[++i])
	{
		if (is_quote(tmp[i]))
			close = search_close_quote(tmp, &i);
	}
	return (close);
}

bool
	is_type_redirect(t_token *token)
{
	return (token->type == TYPE_R_RDRCT
		|| token->type == TYPE_RR_RDRCT
		|| token->type == TYPE_L_RDRCT
		|| token->type == TYPE_LL_RDRCT);
}
