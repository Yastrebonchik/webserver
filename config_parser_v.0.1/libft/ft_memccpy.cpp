/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:06:52 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	unsigned char	sym;

	dest = (unsigned char *)destination;
	src = (unsigned char *)source;
	sym = (unsigned char)c;
	while (n--)
	{
		*dest++ = *src++;
		if (*(dest - 1) == sym)
			return (dest);
	}
	return (NULL);
}
