/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< Updated upstream
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/17 15:46:05 by ytomiyos         ###   ########.fr       */
=======
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/17 15:28:21 by kfumiya          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master	g_master;

void
	free_envs(void)
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
}

int
	all_free()
{
	free_envs();
	return (g_master.exit_cd);
}

void
	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void
	signal_set()
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void
	loop_shell()
{
	t_token *tokens;
	t_node *nodes;
	char *line;

	g_master.environs = environ_init();
	line = NULL;
	while (42)
	{
		line = readline(MS_PROMPT);
		if (line == NULL)
		{
			printf("\n");
			exit(1);
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
<<<<<<< Updated upstream
		del_nodes_list(nodes);
=======
		// del_nodes_list(nodes);
>>>>>>> Stashed changes
	}
}

int	
	main(int ac, char **av)
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
