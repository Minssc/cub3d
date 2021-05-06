/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:11:19 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/06 20:16:11 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_maxi(int a, int b)
{
	return (a < b ? b : a);
}

long long		ft_maxll(long long a, long long b)
{
	return (a < b ? b : a);
}

float			ft_maxf(float a, float b)
{
	return (a < b ? b : a);
}

double			ft_maxd(double a, double b)
{
	return (a < b ? b : a);
}


