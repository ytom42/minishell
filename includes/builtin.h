/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:05:15 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 09:27:36 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "utils.h"
# include "execute.h"

/* 
	builtin.c
 */
int exec_builtin(char **args);
int is_builtin(char **args);

/* 
	builtin_utils.c
 */
char *get_env_value(char *key);
bool is_valid_identifier(char *arg);
t_environ *get_env(char *target);
char *get_cwd_path(char *arg);

/*
	cd.c
 */
int exec_cd(char **args);

/*
	cd_utils.c
 */
bool change_dir(char *dir_path);

/* 
	echo.c
 */
int exec_echo(char **args);

/* 
	env.c
 */
int exec_env(void);

/* 
	env_utils.c
 */
t_environ *new_env (char *key, char *value);
bool append_env(t_environ **envs, t_environ *new);

/* 
	exit.c
 */
int exec_exit(char **args);

/* 
	export.c
 */
int exec_export(char **args);
void sort_envs(t_environ *env);

/* 
	export_utils.c
 */
char **split_key_value(char *arg, char *sep, char *value, bool add_request);
void update_env(char **args);
bool replace_dup_env(char *key, char *value);
void restore_arg(char *sep, bool add_request);


/* 
	pwd.c
 */
int exec_pwd(void);

/* 
	unset.c
 */
int exec_unset(char **args);

#endif
