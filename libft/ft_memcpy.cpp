/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:43:19 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/24 03:09:35 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptrd;
	unsigned const char	*ptrs;

	i = 0;
	ptrd = (unsigned char*)dst;
	ptrs = (unsigned char*)src;
	if (dst != src)
	{
		while (i != n)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	return (dst);
}
