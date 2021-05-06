/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 23:20:08 by minsunki          #+#    #+#             */
/*   Updated: 2021/04/26 15:48:24 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_nl(const char *str)
{
	size_t		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	get_line(char **dat, char **ret)
{
	int		nidx;
	char	*tmp;

	if ((nidx = find_nl(*dat)) != -1)
	{
		*ret = ft_substr(*dat, 0, nidx);
		tmp = *dat;
		*dat = ft_substr(*dat, nidx + 1, -1);
		free(tmp);
		return (1);
	}
	return (0);
}

static int	gnl_eof(char **dat, char **ret)
{
	if (*dat && get_line(dat, ret))
		return (1);
	else if (*dat)
	{
		*ret = *dat;
		*dat = 0;
		return (0);
	}
	*ret = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*dat;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		rbytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((rbytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rbytes] = '\0';
		tmp = dat;
		dat = ft_strjoin(dat, buf);
		(tmp ? free(tmp) : tmp);
		if (get_line(&dat, line))
			return (1);
	}
	if (rbytes < 0)
		return (-1);
	return (gnl_eof(&dat, line));
}
