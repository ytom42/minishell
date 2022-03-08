/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:56:32 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/08 19:05:15 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "common.h"

typedef enum			e_redirect_type
{
	INPUT,
	OUTPUT,
	APPEND_OUTPUT,
	HERE_DOC,
}						t_redirect_type;

typedef struct			s_redirect
{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_redirect_type		type;
	t_token				*filename;
	char				**heredoc;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef struct			s_command
{
	t_token				*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
}						t_command;

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}				t_node_type;

typedef struct	s_node
{
	t_node_type		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

/*
**	parser
*/
t_node	*parser(t_token *token_list);

/*
**	parser_command
*/
t_node	*get_command_node(t_token **token);

/*
**	parser_pipe
*/
t_node	*loop_pipe(t_token **token);

/*
**	node
*/
t_node	*node_new(t_node_type type);
t_redirect	*redirect_new(t_token **token);

/*
**	debug
*/
void	print_nodes(t_node *node_top);

#endif