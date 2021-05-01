/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:46:46 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/28 21:31:41 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
