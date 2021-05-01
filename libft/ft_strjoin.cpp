/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:47:39 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/24 02:17:10 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	newstr_len(char const *s1, char const *s2)
{
	int		len;
	int		ctr;

	ctr = 0;
	len = 0;
	while (s1[ctr] != '\0')
	{
		len++;
		ctr++;
	}
	ctr = 0;
	while (s2[ctr] != '\0')
	{
		len++;
		ctr++;
	}
	return (len);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		cur_i;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	cur_i = 0;
	if (!(new_str = (char*)malloc(newstr_len(s1, s2) * (sizeof(char) + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[cur_i] = s1[i];
		i++;
		cur_i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[cur_i] = s2[i];
		i++;
		cur_i++;
	}
	new_str[cur_i] = '\0';
	return (new_str);
}
