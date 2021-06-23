//
// Created by Karyn Cedra on 6/23/21.
//

#include "utils.hpp"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char*)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	if (!(memory = malloc(count * size)))
		return (NULL);
	ft_bzero(memory, count * size);
	return (memory);
}

static char	**free_memory(char **words_ptr, int cur_word)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = words_ptr;
	while (i < cur_word)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static int	cnt_wrd(char const *s, char c)
{
	int i;
	int	wrd_cnt;

	i = 0;
	wrd_cnt = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			wrd_cnt++;
		}
		else
		{
			i++;
			if (s[i] == '\0')
				wrd_cnt++;
		}
	}
	return (wrd_cnt);
}

static int	cnt_chr(char const *s, int i, char c)
{
	int cnt_char;

	cnt_char = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		cnt_char++;
		i++;
	}
	return (cnt_char);
}

static void	cr_word(char const *s, char *word, int i, int len)
{
	int		cur_len;
	char	*new_word;

	cur_len = 0;
	new_word = word;
	while (cur_len < len)
	{
		new_word[cur_len] = s[i];
		cur_len++;
		i++;
	}
	new_word[cur_len] = '\0';
}

char		**ft_split(char const *s, char c)
{
	char	**words;
	int		cur_word;
	int		chr_quan;
	int		i;

	i = 0;
	cur_word = 0;
	if (!s || !(words = (char**)malloc(sizeof(char*) * (cnt_wrd(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		chr_quan = cnt_chr(s, i, c);
		if (!chr_quan)
			break ;
		if (!(words[cur_word] = (char*)malloc(sizeof(char) * (chr_quan + 1))))
			return (free_memory(words, cur_word));
		cr_word(s, words[cur_word], i, chr_quan);
		cur_word++;
		i += chr_quan;
	}
	words[cur_word] = NULL;
	return (words);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char*)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		i++;
	}
	if (c == 0)
		return (&ptr[i]);
	return (0);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*copy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	if (!(copy = (char*)ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

int		ft_atoi(const char *str)
{
	int		i;
	char	sign;
	int		number;

	i = 0;
	number = 0;
	while (str[i] > 0 && str[i] < 33 && str[i] != '\0' && str[i] != 27)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i];
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10;
		number += str[i] - 48;
		i++;
	}
	if (sign == '-')
		number = number * (-1);
	return (number);
}

static int	newstr_len(char const *s1, char const *s2)
{
	int		len;
	int		ctr;

	ctr = 0;
	len = 0;
	while (s1[ctr] != '\0')
	{
		len++;
		ctr++;
	}
	ctr = 0;
	while (s2[ctr] != '\0')
	{
		len++;
		ctr++;
	}
	return (len);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		cur_i;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	cur_i = 0;
	if (!(new_str = (char*)malloc(newstr_len(s1, s2) * (sizeof(char) + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[cur_i] = s1[i];
		i++;
		cur_i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[cur_i] = s2[i];
		i++;
		cur_i++;
	}
	new_str[cur_i] = '\0';
	return (new_str);
}

static int		add_first_buf(char **text, char *buffer, int size)
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

static int		ft_strchrnum(const char *s, int c)
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