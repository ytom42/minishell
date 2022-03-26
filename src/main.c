/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 12:02:30 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master	g_master;

int
	all_free(void)
{
	t_environ	*env;
	t_environ	*next;

	env = g_master.environs;
	while (env)
	{
		next = env->next;
		free_set((void **)&env->key, NULL);
		free_set((void **)&env->value, NULL);
		free(env);
		env = next;
	}
	env = NULL;
	return (g_master.exit_cd);
}

void
	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void
	info_init(void)
{
	g_master.error_flag = FALSE;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void
	loop_shell(void)
{
	t_token	*tokens;
	t_node	*nodes;
	char	*line;

	g_master.environs = environ_init();
	line = NULL;
	while (42)
	{
		info_init();
		line = readline(MS_PROMPT);
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			system("leaks minishell"); //test
			exit(2);
		}
		else if (ft_strlen(line) > 0)
			add_history(line);
		tokens = lexer(line);
		nodes = parser(tokens);
		exec_nodes(nodes);
		free_set((void **)&line, NULL);
		del_nodes_list(nodes);
		del_tmp_env(g_master.tmp_env);
	}
}

int	main(int ac, char **av)
{
	(void)av;
	info_init();
	g_master.exit_cd = EXIT_SUCCESS;
	if (ac == 1)
		loop_shell();
	else
		printf("Too many arguments\n");
	return (all_free());
}
