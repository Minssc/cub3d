/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:54:10 by minsunki          #+#    #+#             */
/*   Updated: 2021/03/04 21:45:01 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(char const *str, char sep)
{
	int		ret;
	int		is_str;

	ret = 0;
	is_str = 0;
	while (*str)
	{
		if (sep == *str)
		{
			if (is_str)
			{
				ret++;
				is_str = 0;
			}
		}
		else
			is_str = 1;
		str++;
	}
	return (is_str ? ret + 1 : ret);
}

static int	assign_strings(char **arr, char const *str, char sep)
{
	char const	*last;
	int			is_str;

	last = str;
	is_str = 0;
	while (*str)
	{
		if (sep == *str)
		{
			if (is_str && !(*arr++ = ft_substr(last, 0, str - last)))
				return (0);
			is_str = 0;
			last = str;
		}
		else if (!is_str)
		{
			last = str;
			is_str = 1;
		}
		str++;
	}
	if (is_str && !(*arr = ft_substr(last, 0, str - last)))
		return (0);
	return (1);
}

static void	freeall(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;

	if (!s)
		return (0);
	i = count_strings(s, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	ret[i] = 0;
	if (!assign_strings(ret, s, c))
	{
		freeall(ret);
		return (0);
	}
	return (ret);
}
