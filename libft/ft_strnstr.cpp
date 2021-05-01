/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:49:03 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/24 09:52:15 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	loop(char *ptrh, char *ptrn, int i, int len)
{
	int	j;

	j = 0;
	while (ptrh[i] == ptrn[j] && i < len && ptrn[j] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	flag;
	char	*ptrh;
	char	*ptrn;

	i = 0;
	j = 0;
	ptrh = (char*)haystack;
	ptrn = (char*)needle;
	if (ptrn[0] == '\0')
		return (ptrh);
	while (ptrh[i] != '\0' && i < len)
	{
		if (ptrh[i] == ptrn[0])
		{
			flag = i;
			j = loop(ptrh, ptrn, i, len);
			if (ptrn[j] == '\0')
				return (&ptrh[flag]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
