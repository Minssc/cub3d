/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 00:44:34 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/29 13:59:14 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_and_perror(char **spp, char *estr)
{
	int		i;

	i = -1;
	while (spp[++i])
	{
		if (spp[i])
		{
			free(spp[i]);
			spp[i] = 0;
		}
	}
	free(spp);
	perror_exit(estr);
}

int			cp_valid_islice(char *str)
{
	int		ns;
	int		ss;

	ns = 0;
	ss = 0;
	while (*str)
	{
		if (!(*str == ' ' || ft_isdigit(*str)))
			return (0);
		if (ft_isdigit(*str))
		{
			if (ss)
				return (0);
			else
				ns = 1;
		}
		else if (ns && *str == ' ')
			ss = 1;
		str++;
	}
	return (ns);
}

void		cp_col_validate(char *line)
{
	char	**spp;
	int		i;

	i = 0;
	if (!(spp = ft_split(line, ',')))
		free_and_perror(spp, "invalid color");
	while (spp[i])
		i++;
	if (i != 3)
		free_and_perror(spp, "Invalid color (wrong number of elements)");
	while (i--)
	{
		if (!cp_valid_islice(spp[i]))
			free_and_perror(spp, "Invalid color (invalid element)");
		free(spp[i]);
		spp[i] = 0;
	}
	free(spp);
}

void		cp_check_lflag(t_byte *lf, t_byte key)
{
	if (!key && (*lf ^ 63))
		perror_exit("cub data missing key");
	if (*lf & key)
		perror_exit("cub data duplicate key");
	*lf |= key;
}
