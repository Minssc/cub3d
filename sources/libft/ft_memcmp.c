/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:04:06 by minsunki          #+#    #+#             */
/*   Updated: 2021/03/04 02:04:55 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;
	int				ret;

	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	while (n--)
		if ((ret = (*sp1++ - *sp2++)))
			return (ret);
	return (0);
}
