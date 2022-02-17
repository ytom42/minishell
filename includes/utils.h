#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*
 *************
 ** utils **
 *************
 */
/* 
	free.c
*/
void					env_all_free(t_environ *env);
void					env_free(t_environ *env);

/* 
	messeage.c
*/
int						err_msg(char *msg);

#endif
