/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:05:15 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/27 15:59:10 by kfumiya          ###   ########.fr       */
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
int			exec_builtin_cmd(char **args);
int			is_builtin_cmd(char **args);

/* 
	builtin_utils.c
 */
bool		is_valid_identifier(char *arg);
t_environ	*get_env(char *target);
char		*get_cwd_path(char *arg, bool flag);

/*
	cd.c
 */
int			exec_cd(char **args);

/*
	cd_utils.c
 */
bool		change_dir(char *dir_path);

/* 
	echo.c
 */
int			exec_echo(char **args);

/* 
	env.c
 */
t_environ	*environ_init(void);
int			exec_env(void);

/* 
	env_utils.c
 */
t_environ	*new_env(char *key, char *value);
bool		append_env(t_environ **envs, t_environ *new);

/* 
	exit.c
 */
int			exec_exit(char **args);

/* 
	export.c
 */
int			exec_export(char **args);
void		sort_envs(t_environ **env);

/* 
	export_utils.c
 */
void		split_key_value(char *arg, char **sep, \
							char **value, bool *add_request);
void		update_env(char *key, char *new_value, \
						bool add_request, bool is_exp);
bool		replace_dup_env(char *key, char *value, bool is_env);
void		restore_arg(char *sep, bool add_request);
int			envs_size(t_environ *env);

/* 
	pwd.c
 */
int			exec_pwd(void);

/* 
	unset.c
 */
int			exec_unset(char **args);

#endif
