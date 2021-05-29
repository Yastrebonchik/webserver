/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:35:23 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *ptr, int c)
{
	char *res;

	res = NULL;
	if (ptr)
	{
		while (*ptr)
		{
			if (*ptr == c)
				res = (char*)ptr;
			ptr++;
		}
		if (*ptr == c)
			res = (char*)ptr;
	}
	return (res);
}
