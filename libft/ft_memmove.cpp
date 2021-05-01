/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:43:57 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/25 15:11:15 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptrd;
	unsigned char	*ptrs;
	size_t			i;

	i = 0;
	ptrs = (unsigned char*)src;
	ptrd = (unsigned char*)dst;
	if (ptrs > ptrd)
		ft_memcpy(dst, src, len);
	else if (ptrd > ptrs)
	{
		while (len > i)
		{
			len--;
			ptrd[len] = ptrs[len];
		}
	}
	return (dst);
}
