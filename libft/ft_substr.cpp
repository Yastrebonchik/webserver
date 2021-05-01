/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:51:18 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/28 21:06:41 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			cur_len;
	char			*substr;

	if (!s)
		return (NULL);
	if (!(substr = ((char*)malloc((len + 1) * (sizeof(char))))))
		return (NULL);
	if (ft_strlen(s) < start + 1 || len == 0)
	{
		substr[0] = '\0';
		return (substr);
	}
	i = start;
	cur_len = 0;
	while (s[i] != '\0' && cur_len < len)
	{
		substr[cur_len] = s[i];
		i++;
		cur_len++;
	}
	substr[cur_len] = '\0';
	return (substr);
}
