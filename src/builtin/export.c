/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:19:26 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/19 16:21:23 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "libft.h"
#include "expansion.h"

extern t_master	g_master;

void
	print_env(t_environ *env)
{
	char	*expand_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		expand_value = create_value_str(env->value, STATE_IN_DQUOTE, TRUE);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(expand_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(expand_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);	
}

t_environ
	*add_env(t_environ *list, t_environ *new)
{
	t_environ *ret_list;
	t_environ *prev;

	if (list == NULL)
		return (new);
	ret_list = list;
	prev = NULL;
	while (list)
	{
		if (ft_strcmp(list->key, new->key) >= 0)
		{
			new->next = list;
			if (prev)
				prev->next = new;
			else
				return (new);
			return (ret_list);
		}
		prev = list;
		list = list->next;
	}
	prev->next = new;
	return (ret_list);
}

void
	sort_envs(t_environ **env)
{
	t_environ *new;
	t_environ *list;

	list = NULL;
	while (*env)
	{
		new = *env;
		*env = (*env)->next;
		new->next = NULL;
		list = add_env(list, new);
	}
	*env = list;
}

int
	set_envs(char **args)
{
	int		i;
	int		res;
	bool	add_request;
	char	*sep;
	char	*value;

	res = EXIT_SUCCESS;
	i = 0;
	while (args[++i])
	{
		split_key_value(args[i], &sep, &value, &add_request);
		if (is_valid_identifier(args[i]))
			update_env(args[i], value, add_request);
		else
		{
			restore_arg(sep, add_request);
			print_identifier_error("export", args[i]);
			res = EXIT_FAILURE;
		}
	}
	return (res);
}

int
	declare_envs(void)
{
	t_environ		*envs;
	t_environ		*tmp;
	
	envs = dup_envs(g_master.environs);
	if (!envs)
		error_exit(NULL);
	sort_envs(&envs);
	while (envs)
	{
		print_env(envs);
		tmp = envs;
		envs = envs->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

int
	exec_export(char **args)
{
	if (args[1])
		return (set_envs(args));
	else
		return (declare_envs());
	return (EXIT_SUCCESS);
}
