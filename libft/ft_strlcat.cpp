/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:48:12 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/24 16:31:14 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t len1;
	size_t len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	if ((size - 1) < len1 || size == 0)
		return (size + len2);
	while (dst[i] != '\0' && i < (size - 1))
		i++;
	while (src[j] != '\0' && i < (size - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len1 + len2);
}
