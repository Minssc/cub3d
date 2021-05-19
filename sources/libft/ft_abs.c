/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:38:01 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/19 20:39:58 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_absi(int v)
{
	return (v < 0 ? -v : v);
}

long long	ft_absl(long long v)
{
	return (v < 0 ? -v : v);
}

float		ft_absf(float v)
{
	return (v < 0 ? -v : v);
}

double		ft_absd(double v)
{
	return (v < 0 ? -v : v);
}
