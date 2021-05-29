/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:28:46 by rbeach            #+#    #+#             */
/*   Updated: 2020/05/26 14:04:38 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	char			*substr;
	unsigned int	slen;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char*)s;
	slen = ft_strlen(str);
	if (slen < start)
		return (ft_strdup(""));
	if ((substr = (char*)malloc(len + 1)))
	{
		while (len - i && *str)
		{
			substr[i] = str[(int)start + i];
			i++;
		}
		substr[i] = '\0';
	}
	return (substr);
}
