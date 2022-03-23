/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:16:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/23 15:53:32 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *dst)
{
	char	*str;
	size_t	i;

	if (!dst)
		return (NULL);
	str = (char *)malloc(sizeof(*dst) * (ft_strlen(dst) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (dst[i])
	{
		str[i] = dst[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
