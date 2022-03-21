/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:45:28 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/19 19:36:08 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parser(t_token *token_list)
{
	t_node	*node_top;

	if (token_list == NULL)
		return (NULL);
	node_top = loop_pipe(&token_list);
	return (node_top);
}
