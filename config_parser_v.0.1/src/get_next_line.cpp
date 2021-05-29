/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:53:57 by rbeach            #+#    #+#             */
/*   Updated: 2021/05/05 16:02:31 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/config.hpp"

static int	mem_free(char **doc)
{
	free(*doc);
	return (-1);
}

static char	*ft_strschr(const char *str, int c)
{
	char			*ptr;

	if (!str)
		return (NULL);
	ptr = (char*)str;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
}

static int	liner(char **line, char **doc)
{
	int		nl_pos;
	int		nl_s;
	char	*tmp;
	int		doc_len;
	int		line_len;

	tmp = NULL;
	doc_len = ft_strlen(*doc);
	nl_s = ft_strschr(*doc, '\n') ? 1 : 0;
	nl_pos = nl_s ? ft_strschr(*doc, '\n') - *doc : 0;
	line_len = nl_s ? nl_pos : doc_len;
	if (!(*line = ft_substr(*doc, 0, line_len)))
		return (mem_free(doc));
	if (nl_s)
		if (!(tmp = ft_substr(*doc, nl_pos + 1,
		doc_len - ft_strlen(*line) - nl_s)) || !*line)
			return (mem_free(doc));
	free(*doc);
	*doc = tmp;
	return (nl_s);
}

static char		*fuller(char **doc, char *buf)
{
	char	*tmp;

	tmp = NULL;
	if (!*doc)
		return (ft_strdup(buf));
	tmp = ft_strjoin(*doc, buf);
	free(*doc);
	return (tmp);
}

int			get_next_line(int fd, char **line)
{
	static char	*doc[2000];
	char		buf[51];
	int			line_len;

	line_len = 0;
	if (fd < 0 || !line)
		return (-1);
	if (!ft_strschr(doc[fd], '\n'))
		while ((line_len = read(fd, buf, 50)) >= 0)
		{
			buf[line_len] = '\0';
			doc[fd] = fuller(&doc[fd], buf);
			if (ft_strschr(buf, '\n') || !line_len || !doc[fd])
				break ;
		}
	return ((line_len < 0 || !doc[fd]) ? (-1) : (liner(line, &doc[fd])));
}
