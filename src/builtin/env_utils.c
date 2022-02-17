/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:36:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/16 19:09:59 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execute.h"
#include "litft.h"

t_environ
	*new_env(char *key, char *value)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	// new->prev = NULL;
	new->next = NULL;
	return (new);
}

int
	print_env(void)
{
	char	*expand_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	// valueの出力
	if (env->value)
	{
		// value文字列の拡張
		expand_value = expanded_str(env->value, STATUS_DQUOTE, TRUE);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(expand_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(expand_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);	
}

t_bool
	append_env(t_environ **envs, t_environ *new)
{
	t_environ	*tmp;

	if (!new || !envs)
		return (FALSE);
	if (!*envs)
	{
		*envs = new_env;
		return (TRUE);
	}
	tmp = *env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (TRUE);
}

t_environ
	*copy_env(t_environ *env)
{
	t_environ *copy;

	copy = (t_environ *)malloc(sizeof(t_environ));
	if (!copy)
		exit_error();
	copy->key = env->key;
	copy->value = env->value;
	copy->next = NULL;
	return (copy);
}

t_environ
	*dup_env(t_environ *env)
{
	t_environ *res;
	t_environ *tmp;
	t_environ *copy;

	res = NULL;
	tmp = env;
	while (tmp)
	{
		copy = copy_env(tmp);
		if (append_env(&(res), copy))
		{
			set_free(&copy, NULL);
			// exit_error();
		}
		tmp = tmp->next;
	}
	return (res);
}
