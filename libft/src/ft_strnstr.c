/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:28:20 by kfumiya           #+#    #+#             */
/*   Updated: 2020/11/22 11:05:00 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	if (!src[0])
		return ((char *)dst);
	i = 0;
	while (dst[i] && i < len)
	{
		j = 0;
		while (dst[i + j] && src[j] && i + j < len && dst[i + j] == src[j])
			j++;
		if (!src[j])
			return ((char *)(dst + i));
		i++;
	}
	return (NULL);
}
