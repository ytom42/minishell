/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:14:19 by kfumiya           #+#    #+#             */
/*   Updated: 2021/12/05 08:21:39 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(size + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
