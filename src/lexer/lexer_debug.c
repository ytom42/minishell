/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:43:40 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/02/17 19:45:24 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_token(t_token *lst)
{
	int	i;

	i = 1;
	while (lst)
	{
		printf("token[%02d]: %s\n", i, lst->str);
		lst = lst->next;
		i++;
	}
}