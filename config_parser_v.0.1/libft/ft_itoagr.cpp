/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoagr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:36:59 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_calc(int len, int sign, long long num, int gr)
{
	char *res;

	if (!(res = (char*)malloc(len + 1 + sign)))
		return (NULL);
	res[len + sign] = '\0';
	len--;
	while (len >= 0)
	{
		res[len + sign] = (num % gr) > 9 ? (num % gr) + 55 : (num % gr) + '0';
		num /= gr;
		len--;
	}
	if (sign)
		res[0] = '-';
	return (res);
}

char		*ft_itoagr(long long n, int gr)
{
	int				sign;
	int				len;
	long long int	num;

	len = 0;
	sign = n < 0 ? 1 : 0;
	if (n == 0)
		len++;
	num = n;
	while (num)
	{
		num /= gr;
		len++;
	}
	num = n;
	if (num < 0)
		num = -num;
	return (ft_calc(len, sign, num, gr));
}
