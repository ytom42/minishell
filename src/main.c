/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:58:41 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/19 08:54:46 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_exit_status;

int
	all_free(t_master *master)
{
	env_all_free(master->environ);
	free(master->pwd);
	free(master->old_pwd);
	return (g_exit_status);
}

void
	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

int
	init_master(int ac, char **av, t_master *master)
{
	int	status;
	char **str;

	// 下２行はunused variable エラー処理
	status = ac;
	str = av;
	// readline()前のメイン構造体の初期化
	ft_bzero(master, sizeof(t_master));
	// pwdの取得
	master->pwd = getcwd(NULL, 0);
	// -c -iフラグを立てるか
	// filepathのチェック

	// ユーザー環境変数の読み込み、リストに登録
	if (create_env(master))
		return (MS_FALSE);
	// コマンドオプションの追加（<, >, <<...)
	return (MS_SUCCUSE);
}

int
	main(int ac, char **av)
{
	t_master	master;
	int			status;
	bool		debug;

	debug = true;
	// 中断、何もしないシグナルの処理
	if (signal(SIGINT, sigint_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	// master構造体の初期化
	status = init_master(ac, av, &master);
	if (status)
	{
		// printf("check\n");
		all_free(&master);
		return (status);
	}
	if (debug)
	{
		print_env(master.environ);
	}
	ms_loop(&master);
	return (all_free(&master));
}
