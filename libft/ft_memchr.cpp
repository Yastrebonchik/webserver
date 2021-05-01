/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:43:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/28 21:03:54 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char*)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		i++;
	}
	return (0);
}
