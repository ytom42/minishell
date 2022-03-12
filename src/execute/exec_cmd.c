/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:11:56 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/11 18:19:39 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtin.h"
#include "utils.h"
#include "expansion.h"

extern t_master	g_master;

void
	exec_binary_cmd(char **args)
{
	char		**envs;
	char		*path;

	envs = convert_envs(g_master.environs);
	path = create_executable_path(args[0]);
	if (execve(path, args, envs) < 0)
		exit_execve_error(path);
	instant_free(envs);
	free_set((void **)&path, NULL);
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
		error_exit(NULL);
	if (pid == 0)
	{
		if (!args[0])
			exit(EXIT_SUCCESS);
		if (!set_redirects(cmd))
			exit(EXIT_FAILURE);
		if (!dup_redirects(cmd, TRUE))
			exit(EXIT_FAILURE);
		dup_pipe(p_state, old_pipe, new_pipe);
		if (is_builtin_cmd(args))
			exit(exec_builtin_cmd(args));
		else
			exec_binary_cmd(args);
	}
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

static void
	update_pipe_state(t_command *cmd, t_pipe_state *p_state)
{
	if (*p_state == NO_PIPE)
		return ;
	if (cmd->next && cmd->next->next)
		*p_state = PIPE_READ_WRITE;
	else
		*p_state = PIPE_READ_ONLY;
}

int
	exec_command(t_command *cmd, t_pipe_state *p_state, int old_pipe[])
{
	int		exit_cd;
	char	**args;

	exit_cd = EXIT_SUCCESS;
	if (!cmd->redirects->is_heredoc)
		set_heredoc(cmd);
	require_expansion(cmd, &args);
	if (*p_state == NO_PIPE && is_builtin_cmd(args))
		exit_cd = exec_builtin_parent(cmd, args);
	else
		exec_cmd_child(cmd, args, *p_state, old_pipe);
	update_redirects(cmd);
	update_pipe_state(cmd, p_state);
	instant_free(args);
	return (exit_cd);
}
