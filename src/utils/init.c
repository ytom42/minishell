/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:21:08 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/26 21:40:04 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "execute.h"
# include "expansion.h"
# include "utils.h"

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
	g_master.error_fork = FALSE;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void
	check_newline(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return ;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
	return ;
}
