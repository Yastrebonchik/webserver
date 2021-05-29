/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:16:42 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	dest = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	if ((!dest && !src) || !n)
		return (destination);
	if (src >= dest)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		while (n--)
			dest[n] = src[n];
	}
	return (destination);
}
