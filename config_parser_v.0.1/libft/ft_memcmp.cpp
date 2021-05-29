/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:17:44 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t num)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	ptr1 = (unsigned char*)pointer1;
	ptr2 = (unsigned char*)pointer2;
	while (num--)
	{
		if (*ptr1++ != *ptr2++)
			return ((*(--ptr1) - *(--ptr2)));
	}
	return (0);
}
