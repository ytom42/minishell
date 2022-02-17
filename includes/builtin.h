#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"

/*
 *************
 ** builtin **
 *************
 */
/* 
	create_env.c
*/
int						create_env(t_master *master);
int						append_env(t_environ **head, t_environ *new);
t_environ				*new_env(char *key, char *value);

/* 
	create_env.c
*/
int						preset_env(t_master *master);
int						preset_env_pwd_oldpwd(t_master *master);

/* 
	blt_utils.c
*/
void					instant_free(char **str);
t_environ				*search_key(t_environ *env, char *key);
void					release_target(t_environ *target);
void					replace_env_value(t_environ *env, char *new_value);

#endif
