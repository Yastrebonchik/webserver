/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:36:59 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_calc(char *result, int len, int sign, long int num)
{
	result[len + sign] = '\0';
	len--;
	while (len >= 0)
	{
		result[len + sign] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	if (sign)
		result[0] = '-';
}

char		*ft_itoa(int n)
{
	int			sign;
	int			len;
	char		*result;
	long int	num;

	result = NULL;
	len = 0;
	sign = n < 0 ? 1 : 0;
	if (n == 0)
		len++;
	num = n;
	while (num)
	{
		num /= 10;
		len++;
	}
	num = n;
	if (num < 0)
		num = -num;
	if ((result = (char*)malloc(len + 1 + sign)))
		ft_calc(result, len, sign, num);
	return (result);
}
