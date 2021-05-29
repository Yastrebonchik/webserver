/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:17:29 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int				result;
	int				i;

	i = 0;
	if (!src)
		return (0);
	result = ft_strlen(src);
	if (!size)
		return (result);
	while (src[i] != '\0' && i < (int)size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (result);
}
