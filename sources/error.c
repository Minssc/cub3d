/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:13:22 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 19:06:12 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		perror_exit(char *estr)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(estr, 1);
	ft_putchar_fd('\n', 1);
	meta_destroy();
	exit(1);
}
