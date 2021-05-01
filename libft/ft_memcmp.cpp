/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:43:43 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/25 15:28:07 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cpy1;
	unsigned char	*cpy2;

	cpy1 = (unsigned char*)s1;
	cpy2 = (unsigned char*)s2;
	i = 0;
	while (cpy1[i] == cpy2[i] && i < n - 1)
		i++;
	if (i == n)
		return (0);
	else
		return (cpy1[i] - cpy2[i]);
}
