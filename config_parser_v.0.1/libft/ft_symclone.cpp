/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symclone.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:01:20 by rbeach            #+#    #+#             */
/*   Updated: 2021/05/02 16:12:35 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_symclone(char sym, int num)
{
	char *str;

	if ((str = (char *)malloc(num + 1)))
	{
		str[num] = '\0';
		while (num--)
			str[num] = sym;
		return (str);
	}
	return (NULL);
}
