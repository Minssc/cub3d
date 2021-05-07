/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:01:02 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/07 01:37:06 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			map_parse(t_list *list, t_cubd *dat)
{
	t_list	*clist;
	int		lsize;
	int		mmlen;

	clist = list;
	mmlen = 0;
	lsize = 0;
	while (clist)
	{
		printf("l:%s\n",(char *)clist->content);
		//mmlen = ft_maxi(mmlen, ft_strlen((char *)clist->content));
		lsize++;
		clist = clist->next;
	}

	printf("mmlen: %d\n",mmlen);
	return (1);
}
