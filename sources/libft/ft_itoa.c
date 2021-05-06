/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:03:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/03/04 19:52:43 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digs(int n)
{
	int		ret;

	ret = (n <= 0 ? 1 : 0);
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

char		*ft_itoa(int n)
{
	int		dig;
	int		neg;
	char	*ret;

	neg = (n < 0);
	dig = ft_digs(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(ret = (char *)malloc(sizeof(char) * (dig + 1))))
		return (0);
	ret[dig] = 0;
	if (n < 0)
		n = -n;
	while (dig--)
	{
		ret[dig] = '0' + (n % 10);
		n /= 10;
	}
	if (neg)
		ret[0] = '-';
	return (ret);
}
