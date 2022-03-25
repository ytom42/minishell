/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:17:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 19:46:20 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "execute.h"

extern t_master	g_master;

static void
	print_env(t_environ *env)
{
	if (env->value == NULL)
		return ;
	ft_putstr_fd(env->key, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(env->value, STDOUT_FILENO);
}

int
	exec_env(void)
{
	t_environ	*env;

	env = g_master.environs;
	while (env)
	{
		print_env(env);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static t_environ
	*new(void)
{
	t_environ	*env;

	env = (t_environ *)malloc(sizeof(t_environ));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

static void
	add(t_environ **list, t_environ *new)
{
	t_environ	*tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*list = new;
}

t_environ
	*environ_init(void)
{
	extern char		**environ;
	t_environ		*list;
	t_environ		*env;
	int				i;
	char			*sep;

	list = NULL;
	i = 0;
	while (environ[i])
	{
		env = new();
		sep = ft_strchr(environ[i], '=');
		env->key = ft_substr(environ[i], 0, (sep - environ[i]));
		if (ft_strcmp(env->key, "PWD") == 0)
			env->value = getcwd(NULL, 0);
		else
			env->value = ft_strdup(sep + 1);
		add(&list, env);
		i++;
	}
	return (list);
}
