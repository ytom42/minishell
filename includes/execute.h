/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:35:59 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/19 10:59:32 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "libft.h"

# define MS_PROMPT		"$ "

typedef enum e_exit_cd
{
	SCCSS = 0,
	GNRL_ERR = 1,
	DENIED = 126,
	CMD_NOT_FND = 127,
	INVLD_EXT_ARG = 128,
	OUT_OF_EXT_STS = 255,
	INVLD_SYNTX = 258,
}	t_exit_cd;

// 環境変数のリスト
typedef struct s_environ
{
	char *key;
	char *value;
	struct s_environ *next;
} t_environ;

// 実行部メインとなる構造体
typedef struct s_command
{
	t_token				*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
} t_command;

// 入力、解析部分のメインの構造体
typedef struct s_mastetr
{
	// 自作の環境変数リスト
	t_environ *environs;
	// 	終了コード
	t_exit_cd exit_cd;
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
void print_error_filename(char *msg, char *cmd, char *file);

#endif
