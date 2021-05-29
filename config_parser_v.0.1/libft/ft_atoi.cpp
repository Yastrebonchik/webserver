/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:41:38 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(char *str)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\f' || *str == '\r'
	|| *str == '\n' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-' ? -1 : 1);
	while (*str == '0')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		result += (*str - '0');
		if (result > 922337203685477580)
			return ((sign > 0) ? -1 : 0);
		if (!(*(str + 1) >= '0' && (*(str + 1) <= '9')))
			return (result * sign);
		result *= 10;
		str++;
	}
	return (0);
}
