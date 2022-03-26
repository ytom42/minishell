/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:47:44 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 12:09:47 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"

extern t_master	g_master;

static void
	envs_lstsize(t_environ *envs, size_t *size)
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

static char
	*create_env_str(t_environ *environs)
{
	char	*res;

	res = NULL;
	if (environs->key && environs->value)
	{
		res = ft_strjoin(environs->key, "=");
		if (!res)
			error_exit(NULL);
		res = ft_strjoin(res, environs->value);
		if (!res)
			error_exit(NULL);
	}
	else if (!environs->value)
	{
		res = ft_strjoin(environs->key, "=");
		if (!res)
			error_exit(NULL);
		res = ft_strjoin(res, "");
	}
	return (res);
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
		envs[i] = create_env_str(environs);
		environs = environs->next;
	}
	envs[i] = NULL;
	return (envs);
}

bool
	is_heredoc(t_command *cmd)
{
	t_redirect	*redir;

	cmd->is_hdoc = FALSE;
	redir = cmd->redirects;
	if (redir == NULL)
		return (FALSE);
	while (redir)
	{
		if (redir->type == D_LESSER)
		{
			cmd->is_hdoc = TRUE;
			return (TRUE);
		}
		redir = redir->next;
	}
	return (FALSE);
}
