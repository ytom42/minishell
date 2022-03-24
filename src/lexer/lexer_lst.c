/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:35:53 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:08:15 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	get_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return (GREATER);
	else if (ft_strcmp(str, "<") == 0)
		return (LESSER);
	else if (ft_strcmp(str, ">>") == 0)
		return (D_GREATER);
	else if (ft_strcmp(str, "<<") == 0)
		return (D_LESSER);
	else
		return (WORD);
}

t_token	*token_lstnew(char *str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = get_token_type(str);
	new->next = NULL;
	return (new);
}

t_token	*token_lstlast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*token_lstaddback(t_token *lst, t_token *new)
{
	t_token	*last;

	if (!lst)
	{
		lst = new;
	}
	else
	{
		last = token_lstlast(lst);
		last->next = new;
	}
	return (lst);
}

void	token_lstclear(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}
