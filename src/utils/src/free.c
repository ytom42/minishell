/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 08:24:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/11 16:19:01 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void
	env_free(t_environ *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void
	env_all_free(t_environ *env)
{
	t_environ	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_free(tmp);
	}
}
