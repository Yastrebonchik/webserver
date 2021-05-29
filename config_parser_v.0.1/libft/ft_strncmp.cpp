/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:13:53 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	if (!str1 || !str2)
		return (0);
	ptr1 = (unsigned char*)str1;
	ptr2 = (unsigned char*)str2;
	i = 0;
	while (i < num)
	{
		if (ptr1[i] == '\0' && ptr2[i] == '\0')
			return (0);
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
