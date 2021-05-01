/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:50:32 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/28 21:40:32 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_flag(const char *s1, const char *set, int i)
{
	int j;
	int flag;

	j = 0;
	flag = 0;
	while (set[j] != '\0')
	{
		if (set[j] == s1[i])
			flag++;
		j++;
	}
	return (flag);
}

static char	*frst_prt(char const *s1, char const *set, char *tr_str, int i)
{
	int	flag;
	int j;

	flag = 1;
	while (flag > 0)
	{
		flag = ft_flag(s1, set, i);
		i++;
	}
	j = 0;
	i--;
	while (s1[i] != '\0')
	{
		tr_str[j] = s1[i];
		i++;
		j++;
	}
	tr_str[j] = '\0';
	return (tr_str);
}

static char	*scnd_prt(char *tr_str, char const *set)
{
	int flag;
	int i;
	int j;

	flag = 1;
	i = 0;
	j = 0;
	while (tr_str[j] != '\0')
		j++;
	j--;
	while (flag > 0)
	{
		flag = 0;
		while (set[i] != '\0')
		{
			if (set[i] == tr_str[j])
				flag++;
			i++;
		}
		i = 0;
		j--;
	}
	j += 2;
	tr_str[j] = '\0';
	return (tr_str);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	char	*tr_str;
	int		i;

	if (!s1 || !set)
		return (NULL);
	if (!(tr_str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	new_str = frst_prt(s1, set, tr_str, i);
	new_str = scnd_prt(new_str, set);
	tr_str = ft_strdup(new_str);
	free(new_str);
	return (tr_str);
}
