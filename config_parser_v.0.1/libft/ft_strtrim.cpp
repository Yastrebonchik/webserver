/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:16:25 by rbeach            #+#    #+#             */
/*   Updated: 2021/05/02 16:12:25 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trimmer(char const *s1, char const *set, char *newstr)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]) || x)
		{
			newstr[x] = s1[i];
			x++;
		}
		i++;
	}
	newstr[x] = '\0';
	x--;
	while (x >= 0 && ft_strchr(set, newstr[x]))
	{
		newstr[x] = '\0';
		x--;
	}
}

static int	ft_straftertrim(char const *s1, char const *set)
{
	int i;
	int x;
	int result;

	result = 0;
	x = 0;
	while (s1[result] && ft_strchr(set, s1[result]))
		result++;
	i = ft_strlen(s1) - 1;
	while (i != result - 1 && ft_strchr(set, s1[i]))
	{
		x++;
		i--;
	}
	result = ft_strlen(s1) - result - x;
	return (result + 1);
}

char		*ft_strtrim(char const *str1, char const *set)
{
	char	*newstr;
	char	*s1;

	s1 = (char*)str1;
	if (!s1)
		return (NULL);
	if (!set)
	{
		if ((newstr = (char *)malloc(ft_strlen(s1) + 1)))
			newstr[ft_strlen(s1)] = '\0';
	}
	else if ((newstr = (char*)malloc(ft_straftertrim(s1, set))))
		ft_trimmer(s1, set, newstr);
	return (newstr);
}
