/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:45:28 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/25 17:15:21 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

extern t_master	g_master;

t_node	*parser(t_token *token_list)
{
	t_node	*node_top;

	if (token_list == NULL)
		return (NULL);
	node_top = loop_pipe(&token_list);
	if (g_master.error_flag)
		return (del_nodes_list(node_top), NULL);
	return (node_top);
}
