//
// Created by Karyn Cedra on 6/23/21.
//

#include "../includes/utils.hpp"

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

	if (!(memory = operator new(count * size)))
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
		delete(ptr[i]);
		i++;
	}
	delete(ptr);
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
	if (!s || !(words = (char**)operator new(sizeof(char*) * (cnt_wrd(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		chr_quan = cnt_chr(s, i, c);
		if (!chr_quan)
			break ;
		if (!(words[cur_word] = (char*)operator new(sizeof(char) * (chr_quan + 1))))
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
	if (!(substr = ((char*)operator new((len + 1) * (sizeof(char))))))
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

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		cur_i;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	cur_i = 0;
	if (!(new_str = (char*)operator new((ft_strlen(s1) + ft_strlen(s2)) * (sizeof(char) + 1))))
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

std::string	mimeDetect(std::string file) {
	std::string	ret;

	for (std::string::reverse_iterator it = file.rbegin(); *it != '.'; ++it) {
		ret.insert(ret.begin(), *it);
	}
	if (ret.find("html") != std::string::npos)
		ret = "text/html; charset=UTF-8";
	else if (ret.find("css") != std::string::npos)
		ret = "text/css; charset=UTF-8";
	else if (ret.find("js") != std::string::npos)
		ret = "text/css; charset=UTF-8";
	else if (ret.find("png") != std::string::npos)
		ret = "image/png";
	else if (ret.find("jpg") != std::string::npos || ret.find("jpeg") != std::string::npos
	|| ret.find("jfif") != std::string::npos || ret.find("pjpeg") != std::string::npos
	|| ret.find("pjp") != std::string::npos)
		ret = "image/jpeg";
	else if (ret.find("ico") != std::string::npos)
		ret = "image/png";
	else if (ret.find("woff") != std::string::npos)
		ret = "font/woff";
	else if (ret.find("ttf") != std::string::npos)
		ret = "font/ttf";
	else if (ret.find("otf") != std::string::npos)
		ret = "font/ttf";
	else if (ret.find("less") != std::string::npos)
		ret = "text/plain";
	else
		ret = "text/plain";
	return (ret);
}

std::string	listing(std::string directory) {
	struct stat		*buf = (struct stat *) operator new(sizeof(struct stat));
	struct dirent 	*entry;
	std::string 	file;
	std::string 	ret;
	DIR 			*dir;

	dir = opendir(directory.c_str());
	if (dir == NULL)
		return ("");
	ret += "<html>\n"
		   "<head><title>Index of /</title></head>\n"
		   "<body bgcolor=\"white\">\n"
		   "<h1>Index of /</h1><hr><pre><a " + directory + "</a>\n";
	while ((entry = readdir(dir)) != NULL) {
		ret += "<a href=\"";
		file = entry->d_name;
		stat(file.c_str(), buf);
		if (S_ISDIR(buf->st_mode)) {
			ret += file + "/\">" + file + "/" + "</a>\n";
		}
		else {
			ret += file + "\">" + file + "</a>\n";
		}
	}
	ret += "</pre><hr></body>\n"
		   "</html>";
	return (ret);
}