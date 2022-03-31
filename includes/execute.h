/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:35:59 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/31 20:06:59 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "utils.h"
# include "expansion.h"
# include "common.h"

typedef enum e_pipe_state
{
	NO_PIPE,
	PIPE_READ_ONLY,
	PIPE_WRITE_ONLY,
	PIPE_READ_WRITE
}	t_pipe_state;

typedef enum e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
}	t_cmd_type;

void			exec_nodes(t_node *nodes);

/*
	exec_cmd.c
*/
int				exec_command(t_command *cmd, \
								t_pipe_state *p_state, int old_pipe[]);
void			exec_binary_cmd(char **args);

/*
	error_1.c
*/
void			print_identifier_error(char *cmd, char *arg);
void			print_error_msg(char *msg, char *cmd);
void			error_exit(char *cmd);
void			print_num_arg_error(char *arg);
void			print_cwd_error(char *arg);

/*
	error_2.c
*/
void			print_filename_error(char *msg, char *cmd, char *file);
void			print_fd_error(int fd);
void			exit_execve_error(char *path);
void			print_syntax_error(char *token);
void			print_enclosed_error(void);

/*
	error_3.c
*/
void			print_fork_error(void);

/*
	redirect.c
*/
bool			set_redirects(t_command *cmd);
bool			dup_redirects(t_command *cmd, bool is_parent);
void			update_redirects(t_command *cmd);

/*
	pipe.c
*/
void			create_pipe(t_pipe_state p_state, int new_pipe[]);
int				dup_pipe(t_pipe_state p_state, int old_pipe[], int new_pipe[]);
void			update_pipe(t_pipe_state p_state, \
							int old_pipe[], int new_pipe[]);

/*
	check_executable.c
*/
bool			is_command(char *path);
bool			is_executable(char *path);
bool			check_executable_cmd(char *path);

/*
	create_path.c
*/
char			*create_executable_path(char *cmd);
char			*search_cmd_path(char *cmd);
void			create_cmd_path(char **split_paths, \
							char **executable_path, char *cmd);

/*
	exec_utils.c
*/
char			**convert_envs(t_environ *environs);
bool			require_expansion(t_command *cmd, char ***args);
bool			is_heredoc(t_command *cmd);

/*
	wait_process.c
*/
void			wait_process(t_command *cmd);

/*
	require_expantion.c
*/
bool			require_expansion(t_command *cmd, char ***args);

/*
	heredoc.c
*/
void			set_heredoc(t_command *cmd);

/*
	heredoc_utils.c
*/
void			create_heredoc_pipe(t_redirect *redir);
void			write_heredoc(t_redirect *redir);
void			set_hdoc_pipe(int hdoc_pipe[]);
void			add_heredoc(t_command *cmd, t_heredoc *hdoc);

/*
	exec_utils_2.c
*/
t_heredoc		*get_hdoc(t_redirect *redir);
void			update_pipe_state(t_command *cmd, t_pipe_state *p_state);
void			update_info(t_command *cmd, t_pipe_state *p_state, char **args);
t_token_state	close_qoute_filename(char *str);

/*
	exec_utils_2.c
*/
bool			skip_redirect(t_redirect **redir, char *org_filename);

#endif
