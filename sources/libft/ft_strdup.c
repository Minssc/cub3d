/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:10:54 by minsunki          #+#    #+#             */
/*   Updated: 2021/03/04 23:06:15 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	slen;
	char	*nstr;

	slen = ft_strlen(str);
	if (!(nstr = (char *)malloc(sizeof(char) * (slen + 1))))
		return (0);
	ft_strlcpy(nstr, str, slen + 1);
	return (nstr);
}
