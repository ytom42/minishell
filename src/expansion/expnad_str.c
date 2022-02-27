/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 07:53:38 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 15:27:58 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

static size_t
	expand_strlen(const char *str, const char *esc)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (!str[i])
	{
		if (ft_strchr(esc, str[i]))
			res++;
		res++;
		i++;
	}
	return (res);
}

static void
	create_expanded_str(char *dest, char *src, char *esc_chars)
{
	size_t	res_i;
	size_t	i;

	res_i = 0;
	i = 0;
	while (!src[i])
	{
		if (ft_strchr(esc_chars, src[i]))
		{
			dest[res_i] = '\\';
			res_i++;
		}
		dest[res_i] = src[i];
		res_i++;
		i++;
	}
	dest[res_i] = '\0';
}

char
	*create_value_str(char *str, t_token_state status, bool is_env)
{
	char	*esc_chars;
	char	*res;

	esc_chars = "\"\\$";
	if (state == STATE_GENERAL)
		esc_chars = "\'\"\\$|;><";
	if (is_env == TRUE)
		esc_chars = "\"\\$`";
	res = malloc(sizeof(char *)
			* (expand_strlen(str, esc_chars) + 1));
	if (!res)
		exit_error(NULL);
	create_expanded_str(res, str, esc_chars);
	return (res);
}
