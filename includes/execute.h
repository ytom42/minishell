/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:35:59 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 15:21:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "libft.h"

typedef enum e_exit_cd
{
	SCCSS = 0,
	GNRL_ERR = 1,
	DENIED = 13,
	CMD_NOT_EXEC = 126,
	CMD_NOT_FND = 127,
	INVLD_EXT_ARG = 128,
	OUT_OF_EXT_STS = 255,
	INVLD_SYNTX = 258,
} t_exit_cd;

typedef enum e_bool
{
	FALSE,
	TRUE,
} t_bool;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SEMICOLON,
} t_node_type;

// 環境変数のリスト
typedef struct s_environ
{
	char *key;
	char *value;
	struct s_environ *next;
} t_environ;

typedef struct			s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*str;
} t_token;

typedef struct	s_node
{
	t_node_type		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct			s_redirect
{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_redirect_type		type;
	t_token				*filename;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;
typedef struct s_command
{
	t_token				*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
} t_command;

typedef enum e_pipe_state
{
	NO_PIPE,
	PIPE_READ_ONLY,
	PIPE_WRITE_ONLY,
	PIPE_READ_WRITE
} t_pipe_state;

typedef enum e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT
} t_redirect_type;

typedef enum e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
} t_cmd_type;

// 全体の情報管理
typedef struct s_mastetr
{
	// 自作の環境変数リスト
	t_environ	*environs;
	// 	終了コード
	int			exit_cd;
} t_master;

/*
	exec_cmd.c
*/

/*
	error.c
*/
void print_identifier_error(char *cmd, char *arg);
void print_error_msg(char *msg, char *cmd);
void error_exit(char *cmd);
void print_num_arg_error(char *arg);
void print_cwd_error(char *arg);
void print_filename_error(char *msg, char *cmd, char *file);

/*
	redirect.c
*/
bool set_redirects(t_command *cmd);
bool dup_redirects(t_command *cmd, bool is_parent);


#endif
