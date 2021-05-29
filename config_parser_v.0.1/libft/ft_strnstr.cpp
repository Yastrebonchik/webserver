/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:45:31 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *little, size_t len)
{
	int		i;
	int		j;

	if (!*little)
		return ((char *)dest);
	if (!dest || !len)
		return (NULL);
	while (*dest && len)
	{
		i = 0;
		j = len;
		while (little[i] && dest[i] && little[i] == dest[i] && j--)
			i++;
		if (!little[i])
			return ((char *)dest);
		dest++;
		len--;
	}
	return (NULL);
}
