/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:56:11 by rbeach            #+#    #+#             */
/*   Updated: 2020/07/30 12:06:40 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_counter(char const *s, char c)
{
	char	*str;
	int		size;
	int		i;

	size = 0;
	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			size++;
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			size++;
		i++;
	}
	return (size);
}

static int	ft_free_result(char **res, int w_count)
{
	while (w_count >= 0)
	{
		free(res[w_count]);
		res[w_count] = NULL;
		w_count--;
	}
	free(res);
	res = NULL;
	return (0);
}

static int	ft_malloc(char const *s, char c, char **res)
{
	int		i;
	char	*str;
	int		w_size;
	int		w_count;

	str = (char *)s;
	w_count = 0;
	i = 0;
	w_size = 0;
	while (str[i])
	{
		if (str[i] != c)
			w_size++;
		if ((str[i] == c || !str[i + 1]) && w_size)
		{
			if (!(res[w_count] = (char*)malloc(w_size + 1)))
				return (ft_free_result(res, w_count));
			w_size = 0;
			w_count++;
		}
		i++;
	}
	return (1);
}

static void	ft_fuller(char const *s, char c, char **res)
{
	int		i;
	char	*str;
	int		w_i;
	int		w_count;

	str = (char *)s;
	w_count = 0;
	i = 0;
	w_i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			res[w_count][w_i] = str[i];
			w_i++;
		}
		if ((str[i] == c || !str[i + 1]) && w_i)
		{
			res[w_count][w_i] = '\0';
			w_i = 0;
			w_count++;
		}
		i++;
	}
}

char		**ft_split(char const *s, char c)
{
	char	**res;
	int		w_count;

	res = NULL;
	if (!s)
		return (res);
	w_count = ft_size_counter(s, c);
	if ((res = (char **)malloc(sizeof(char*) * (w_count + 1))))
	{
		if (!ft_malloc(s, c, res))
			return (NULL);
		ft_fuller(s, c, res);
		res[w_count] = NULL;
	}
	return (res);
}
