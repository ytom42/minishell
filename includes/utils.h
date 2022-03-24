#ifndef UTILS_H
# define UTILS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <stddef.h>
# include <stdbool.h>
# include "common.h"
# include "libft.h"

/* 
	free.c
*/
void	free_set(void **dst, void *src);
void	instant_free(char **str);
void	del_token(t_token *token);
void	*del_token_list(t_token *token);
void	del_nodes_list(t_node *nodes);
void	del_tmp_env(t_environ **envs);

/* 
	str.c
*/
bool	str_is_digit(char *str);
char	*ft_strcpy_forward(char *dest, char *src);

/* 
	path.c
*/
char	*join_path(char *front, char *back);
bool	is_directory(const char *path);

/* 
	env_utils.c
*/
t_environ	*dup_envs(t_environ *env);
t_environ	*dup_env(t_environ *env);
char		*get_env_value(char *key);

/* 
	path_canonicalisation.c
*/
char	*path_canonicalisation(char *path);


#endif
