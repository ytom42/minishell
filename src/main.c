/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/22 15:24:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master g_master;

void free_envs(void)
{
	t_environ *env;
	t_environ *next;

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
}

int all_free()
{
	free_envs();
	return (g_master.exit_cd);
}

void handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void signal_set()
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void loop_shell()
{
	t_token *tokens;
	t_node *nodes;
	char *line;

	g_master.environs = environ_init();
	line = NULL;
	while (42)
	{
		signal_set();
		line = readline(MS_PROMPT);
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (ft_strlen(line) > 0)
		{
			add_history(line);
		}
		tokens = lexer(line);
		// print_token(tokens);  //debug
		nodes = parser(tokens);
		// print_nodes(nodes);   //debug
		exec_nodes(nodes);
		free_set((void **)&line, NULL);
		del_nodes_list(nodes);
		// printf("%d\n", g_master.exit_cd);
	}
}

int main(int ac, char **av)
{
	(void)av;
	signal_set();
	g_master.exit_cd = EXIT_SUCCESS;
	if (ac == 1)
	{
		loop_shell();
	}
	else
	{
		printf("Too many arguments\n");
	}
	return (all_free());
}
