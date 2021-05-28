/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:27:26 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:57:16 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			mexit(int ec)
{
	meta_destroy();
	exit(1);
}

void			perror_exit(char *estr)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(estr, 1);
	ft_putchar_fd('\n', 1);
	mexit(1);
}
