#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <sys/stat.h>
# include <stddef.h>

/*
 *************
 ** utils **
 *************
 */
/* 
	free.c
*/
void free_set(void **dst, void *src);
void instant_free(char **str);

/* 
	str.c
*/
t_bool str_is_digit(char *str);
char *ft_strcpy_forward(char *dest, char *src);


/* 
	path.c
*/
char *join_path(char *front, char *back);
bool is_directory(const char *path);

/* 
	env_utils.c
*/
t_environ *dup_envs(t_environ *env);
t_environ *dup_env(t_environ *env);
char	*get_env_value(char *key);

#endif
