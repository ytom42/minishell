/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/08 19:26:13 by kfumiya          ###   ########.fr       */
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
	// free(master->pwd);
	// free(master->old_pwd);
	return (g_master->exit_cd);
}

// void
// 	sigint_handler(int sig)
// {
// 	(void)sig;
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_exit_status = 1;
// }

// int
// 	init_master(void)
// {
	// int	status;
	// char **str;

	// // 下２行はunused variable エラー処理
	// status = ac;
	// str = av;
	// // readline()前のメイン構造体の初期化
	// ft_bzero(g_master, sizeof(t_master));
	// if (!g_master)
	// 	error_exit(NULL);
	// ft_bzero(g_master.environs, sizeof(t_environ));
	
	// pwdの取得
	// master->pwd = getcwd(NULL, 0);
	// // -c -iフラグを立てるか
	// // filepathのチェック

	// // ユーザー環境変数の読み込み、リストに登録
	// if (create_env(master))
	// 	return (MS_FALSE);
	// コマンドオプションの追加（<, >, <<...)
	// return (MS_SUCCUSE);
// }

// int
// 	main(int ac, char **av)
// {
// 	t_master	master;
// 	int			status;
// 	bool		debug;

// 	debug = true;
// 	// 中断、何もしないシグナルの処理
// 	if (signal(SIGINT, sigint_handler) == SIG_ERR
// 		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 		return (1);
// 	// master構造体の初期化
// 	status = init_master(ac, av, &master);
// 	if (status)
// 	{
// 		// printf("check\n");
// 		all_free(&master);
// 		return (status);
// 	}
// 	if (debug)
// 	{
// 		print_env(master.environ);
// 	}
// 	ms_loop(&master);
// 	return (all_free(&master));
// }

void
	loop_shell()
{
	t_token *tokens;
	t_node *nodes;
	char *line;

	line = NULL;
	while (42)
	{
		line = readline(MS_PROMPT);
		add_history(line);
		// lexser
		tokens = lexer(*line)
		// perser
		nodes = paser(tokens);
		// expansion, execute
		exec_nodes(nodes);
		free_set((void **)&line, NULL);
		del_tokens_list(tokens);
		del_nodes_list(nodes);
	}
}

int	
	main(int ac, char **av)
{
	g_master.exit_cd = EXIT_SUCCESS;
	// signal
	if (ac == 1)
	{
		loop_shell();
	}
	else
	{
		printf("Too many arguments\n")
	}
	return (all_free());
}
