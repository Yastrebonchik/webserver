/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 21:50:40 by student           #+#    #+#             */
/*   Updated: 2020/05/29 00:41:32 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptrd;
	unsigned char	*ptrs;
	unsigned char	chr;

	i = 0;
	chr = c;
	ptrd = (unsigned char*)dst;
	ptrs = (unsigned char*)src;
	if (dst != src)
	{
		while (i != n)
		{
			ptrd[i] = ptrs[i];
			if (ptrs[i] == chr)
			{
				i++;
				return (&ptrd[i]);
			}
			i++;
		}
	}
	return (NULL);
}
