/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:47:44 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/26 15:45:17 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"
#include "libft.h"

extern t_master	g_master;

void
	envs_listsize(t_environ *envs, size_t *size)
{
	t_environ	*tmp;

	*size = 0;
	tmp = envs;
	while (tmp)
	{
		(*size)++;
		tmp = tmp->next;
	}
}

void
	creat_env_str(t_environ *environs, char *env_str)
{
	char	*tmp;

	if (environs->value && environs->is_env)
	{
		env_str = ft_strjoin(environs->key, "=");
		if (!env_str)
			error_exit(NULL);
		tmp = env_str;
		env_str = ft_strjoin(env_str, environs->value);
		if (!env_str)
			error_exit(NULL);
		free_set((void **)&tmp, NULL);
	}
}

char
	**convert_envs(t_environ *environs)
{
	char	**envs;
	size_t	size;
	size_t	i;

	envs_lstsize(environs, &size);
	envs = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envs)
		error_exit(NULL);
	i = -1;
	while (++i < size)
	{
		create_env_str(environs, envs[i]);
		environs = environs->next;
	}
	envs[i] = NULL;
	return (envs);
}
