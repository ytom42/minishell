/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:56:32 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/24 20:18:08 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

/*
**	parser
*/
t_node		*parser(t_token *token_list);

/*
**	parser_command
*/
t_node		*get_command_node(t_token **token, t_parse_info *info);

/*
**	parser_pipe
*/
t_node		*loop_pipe(t_token **token);

/*
**	node
*/
t_node		*node_new(t_node_type type);
t_redirect	*redirect_new(t_token **token);

/*
**	debug
*/
void		print_nodes(t_node *node_top);

#endif