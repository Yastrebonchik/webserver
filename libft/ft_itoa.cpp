/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:40:29 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/27 16:21:12 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_exception(void)
{
	char	*s;

	s = ft_strdup("-2147483648");
	return (s);
}

static char	*ft_itoa_neg(int nb, int copy)
{
	int		len;
	char	*s;

	if (nb == -2147483648)
		return (ft_exception());
	nb = nb * (-1);
	len = 0;
	while (copy / 10 != 0)
	{
		copy = copy / 10;
		len++;
	}
	len += 2;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (len != 0)
	{
		len--;
		s[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	s[0] = '-';
	return (s);
}

char		*ft_itoa(int nb)
{
	int		len;
	int		copy;
	char	*s;

	if (nb < 0)
		return (ft_itoa_neg(nb, nb));
	copy = nb;
	len = 0;
	while (copy / 10 != 0)
	{
		copy = copy / 10;
		len++;
	}
	len += 1;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (len != -1)
	{
		len--;
		s[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (s);
}
