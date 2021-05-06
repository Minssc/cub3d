/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:12:37 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/06 20:17:51 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_mini(int a, int b)
{
	return (a < b ? a : b);
}

long long	ft_minll(long long a, long long b)
{
	return (a < b ? a : b);
}

float		ft_minf(float a, float b)
{
	return (a < b ? a : b);
}

double		ft_mind(double a, double b)
{
	return (a < b ? a : b);
}
