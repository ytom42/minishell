/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:28:28 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/13 03:04:34 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long
	ft_abs(long long num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

static int
	ft_check_length(int len, long num)
{
	int	length;

	length = len;
	while (num > 0)
	{
		num /= 10;
		length++;
	}
	return (length);
}

static void
	ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	tmp;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
}

char
	*ft_itoa(int n)
{
	char		*str;
	int			sign;
	size_t		len;
	long long	tmp;

	sign = (n < 0);
	len = (n == 0);
	tmp = ft_abs(n);
	len = ft_check_length(len, tmp);
	str = ft_calloc(len + sign + 1, sizeof(*str));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len++] = ft_abs(n % 10) + '0';
		n = (n / 10);
	}
	if (sign)
		str[len] = '-';
	ft_strrev(str);
	str[++len] = '\0';
	return (str);
}
