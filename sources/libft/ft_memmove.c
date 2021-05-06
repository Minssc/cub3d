/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:20:59 by minsunki          #+#    #+#             */
/*   Updated: 2021/03/04 20:08:46 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *pd;
	unsigned char *ps;

	pd = (unsigned char *)dest;
	ps = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (pd < ps)
	{
		while (n--)
			*pd++ = *ps++;
	}
	else
	{
		while (n--)
			pd[n] = ps[n];
	}
	return (dest);
}
