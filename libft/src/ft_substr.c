/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:28:31 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/12 23:55:39 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char
	*ft_alloc(char const *s, size_t length, size_t start, size_t len)
{
	char	*str;

	if (length - start >= len)
	{
		str = (char *)malloc(sizeof(*s) * (len + 1));
		if (!str)
			return (NULL);
	}
	else
	{
		str = (char *)malloc(sizeof(*s) * (length - start + 1));
		if (!str)
			return (NULL);
	}
	return (str);
}

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	*str;

	if (!s)
		return (0);
	length = ft_strlen(s);
	if (len <= 0 || length <= start)
		return (str = ft_strdup("\0"));
	str = ft_alloc(s, length, start, len);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
