/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:37:55 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/24 19:39:37 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_text(char **text)
{
	free(*text);
	*text = NULL;
}

static int	sub_str_join(char **text, char *buffer, int size)
{
	char	*substr;
	char	*collat;

	substr = ft_substr(buffer, 0, size);
	collat = ft_strjoin(*text, substr);
	free(*text);
	*text = ft_substr(collat, 0, ft_strlen(collat));
	if (substr)
		free(substr);
	if (collat)
		free(collat);
	if (*text == NULL)
		return (-1);
	return (0);
}

static int	if_text_slash_n(char **line, char **text, char *buffer, int fd)
{
	int		size;
	char	*collat;

	size = BUFFER_SIZE;
	if (*text[0] == '\n')
		*line = ft_substr(*text, 0, 0);
	else
		*line = ft_substr(*text, 0, ft_strchrnum(*text, '\n'));
	collat = ft_substr(*text, ft_strchrnum(*text, '\n') + 1, ft_strlen(*text)
	- ft_strchrnum(*text, '\n') - 1);
	free(*text);
	*text = ft_strjoin(collat, "\0");
	if (collat)
		free(collat);
	if (*text[0] == '\0' && text != NULL && fd != 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == 0)
			free_text(text);
		else
			fd = sub_str_join(text, buffer, size);
	}
	return ((fd == -1 || (text == NULL && size != 0)) ? -1 : 0);
}

static int	main_loop(char **line, char **text, char *buffer, int fd)
{
	int		size;
	int		error;

	error = 0;
	size = BUFFER_SIZE;
	while (error != -1 && ft_strchrnum(*text, '\n') == 0 && size == BUFFER_SIZE
		&& *text[0] != '\n')
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size != 0)
			error = sub_str_join(text, buffer, size);
	}
	if (error != -1 && ft_strchrnum(*text, '\n') == 0 && size != BUFFER_SIZE)
	{
		*line = ft_strjoin(*text, "\0");
		free_text(text);
		return (0);
	}
	else if (error != -1 && (ft_strchrnum(*text, '\n') != 0 ||
	*text[0] == '\n'))
		error = if_text_slash_n(line, text, buffer, fd);
	if (*line == NULL || error == -1)
		return (-1);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char *text = NULL;
	int			size;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (text == NULL)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size <= 0)
		{
			*line = ft_strjoin("\0", "\0");
			return (size);
		}
		if (add_first_buf(&text, buffer, size) == -1)
			return (-1);
		return (main_loop(line, &text, buffer, fd));
	}
	else
		return (main_loop(line, &text, buffer, fd));
}
