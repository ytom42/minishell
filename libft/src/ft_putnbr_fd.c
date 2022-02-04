/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 10:51:21 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/12 23:26:41 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

void
	ft_putnbr_fd(int n, int fd)
{
	char	str[13];
	int		sign;
	int		len;

	sign = (n < 0);
	ft_bzero(str, 13);
	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[len] = '-';
	else if (len > 0)
		len--;
	while (len >= 0)
		write(fd, &str[len--], 1);
}
