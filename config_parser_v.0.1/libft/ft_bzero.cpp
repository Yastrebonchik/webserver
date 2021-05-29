/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:22 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	if (!s || !n)
		return ;
	i = 0;
	ptr = (unsigned char*)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
