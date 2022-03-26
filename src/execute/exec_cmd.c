/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:11:56 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 21:33:06 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtin.h"
#include "utils.h"
#include "expansion.h"

extern t_master	g_master;

void
	exec_binary_cmd(char **args, t_command *cmd)
{
	char		**envs;
	char		*path;
	t_heredoc	*hdoc;

	hdoc = get_hdoc(cmd->redirects);
	if (hdoc)
		set_hdoc_pipe(hdoc->hdoc_pipe);
	envs = convert_envs(g_master.environs);
	path = create_executable_path(args[0]);
	if (execve(path, args, envs) < 0)
		exit_execve_error(path);
}

void
	exec_cmd(char **args, t_command *cmd)
{
	if (is_builtin_cmd(args))
		exit(exec_builtin_cmd(args));
	else
		exec_binary_cmd(args, cmd);
}

static void
	exec_cmd_child(t_command *cmd, char **args,
					t_pipe_state p_state, int old_pipe[])
{
	pid_t	pid;
	int		new_pipe[2];

	create_pipe(p_state, new_pipe);
	pid = fork();
	if (pid == -1)
	{
		g_master.error_fork = TRUE;
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!args[0])
			exit(EXIT_SUCCESS);
		if (!set_redirects(cmd) || !dup_redirects(cmd, TRUE))
			exit(EXIT_FAILURE);
		dup_pipe(p_state, old_pipe, new_pipe);
		exec_cmd(args, cmd);
	}
	else
		signal(SIGINT, SIG_IGN);
	update_pipe(p_state, old_pipe, new_pipe);
	cmd->pid = pid;
}

static int
	exec_builtin_parent(t_command *cmd, char **args)
{
	if (!set_redirects(cmd))
		return (EXIT_FAILURE);
	if (!dup_redirects(cmd, TRUE))
		return (EXIT_FAILURE);
	return (exec_builtin_cmd(args));
}

int
	exec_command(t_command *cmd, t_pipe_state *p_state, int old_pipe[])
{
	int			exit_cd;
	char		**args;

	exit_cd = EXIT_SUCCESS;
	if (is_heredoc(cmd))
	{
		set_heredoc(cmd);
		create_heredoc_pipe(cmd->redirects);
	}
	require_expansion(cmd, &args);
	if (g_master.error_flag)
	{
		instant_free(args);
		return (print_enclosed_error(), 0);
	}
	if (*p_state == NO_PIPE && is_builtin_cmd(args))
		exit_cd = exec_builtin_parent(cmd, args);
	else
	{
		exec_cmd_child(cmd, args, *p_state, old_pipe);
		if (cmd->is_hdoc)
			write_heredoc(cmd->redirects);
	}
	update_info(cmd, p_state, args);
	return (exit_cd);
}
