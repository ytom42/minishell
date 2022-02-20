/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:35:53 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/02/20 15:36:21 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_lstnew(char *str)
{
	t_token	*new;

	new = (t_token*)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	// new->prev = NULL;
	new->str = str;
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
	t_token *last;

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
