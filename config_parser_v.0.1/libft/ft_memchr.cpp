/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:50:14 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	unsigned char *res;

	res = (unsigned char*)ptr;
	while (count--)
		if (*res++ == (unsigned char)ch)
			return (--res);
	return (NULL);
}
