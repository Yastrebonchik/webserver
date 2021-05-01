/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:50:10 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/22 23:50:13 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		flag;
	int		last;
	char	*ptr;

	i = 0;
	last = 0;
	flag = 0;
	ptr = (char*)s;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == c)
		{
			flag++;
			last = i;
		}
		i++;
	}
	if (c == 0)
		return (&ptr[i]);
	if (flag > 0)
		return (&ptr[last]);
	else
		return (0);
}
