/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 07:57:21 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/19 09:21:55 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

void
	print_line(char *line)
{
	printf("%s\n", line);
}

void
	print_tokens(t_token *head)
{
	t_token	*token;
	int i;

	i = 0;
	token = head;
	while (token)
	{
		printf("=====================================\n");
		printf("token_[%d]\n", i);
		printf("token : 	%s\n", token->token);
		printf("type : 		%d\n\n", token->type);
		printf("=====================================\n");
		token = token->next;
		i++;
	}
}

void
	print_env(t_environ *head)
{
	t_environ	*env;

	env = head;
	printf("===my_env=============================\n");
	printf("key: %s\n", env->key);
	// while (env)
	// {
	// 	// key : value
	// 	printf("%s : %s\n", env->key, env->value);
	// 	env = env->next;
	// }
	printf("=====================================\n");

}
