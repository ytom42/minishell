/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:31:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 20:26:26 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <stddef.h>
# include <stdbool.h>
# include "common.h"
# include "libft.h"

/* 
	free_1.c
*/
void		free_set(void **dst, void *src);
void		instant_free(char **str);
void		del_token(t_token *token);
void		*del_token_list(t_token *token);
void		del_tmp_env(t_environ *envs);

/* 
	free_2.c
*/
void		del_nodes_list(t_node *nodes);

/* 
	str.c
*/
bool		str_is_digit(char *str);
char		*ft_strcpy_forward(char *dest, char *src);

/* 
	path.c
*/
char		*join_path(char *front, char *back);
bool		is_directory(const char *path);

/* 
	env_utils.c
*/
t_environ	*dup_envs(t_environ *env);
t_environ	*dup_env(t_environ *env);
char		*get_env_value(char *key);

/* 
	path_canonicalisation.c
*/
char		*path_canonicalisation(char *path);

/*
	init.c
*/
int			all_free(void);
void		info_init(void);
void		check_newline(char *line);

#endif
