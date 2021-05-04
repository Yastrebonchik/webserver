/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 11:32:22 by kcedra            #+#    #+#             */
/*   Updated: 2020/07/24 01:43:03 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		add_first_buf(char **text, char *buffer, int size)
{
	char	*substr;

	substr = ft_substr(buffer, 0, size);
	*text = ft_strjoin(substr, "\0");
	if (substr)
		free(substr);
	if (*text == NULL)
		return (-1);
	return (0);
}

int		ft_strchrnum(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char*)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == c)
			return (i);
		i++;
	}
	if (c == 0)
		return (i);
	return (0);
}
