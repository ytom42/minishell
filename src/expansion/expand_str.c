/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 07:53:38 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 17:16:10 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execute.h"

static void
	create_expanded_str(char *dest, char *src)
{
	size_t	res_i;
	size_t	i;

	res_i = 0;
	i = 0;
	if (src)
	{
		while (src[i])
		{
			dest[res_i] = src[i];
			res_i++;
			i++;
		}
		dest[res_i] = '\0';
	}
}

char
	*create_value_str(char *str)
{
	char	*res;

	res = NULL;
	if (!str)
		return (res);
	res = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!res)
		error_exit(NULL);
	create_expanded_str(res, str);
	return (res);
}
