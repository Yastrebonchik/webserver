/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:28:31 by rbeach            #+#    #+#             */
/*   Updated: 2021/05/02 16:09:17 by rbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

	void *ft_memset(void *s, int c, size_t n);
	void ft_bzero(void *s, size_t n);
	void *ft_memcpy(void *dest, const void *src, size_t n);
	void *ft_memccpy(void *dest, const void *src, int c, size_t n);
	void *ft_memmove(void *dest, const void *src, size_t n);
	void *ft_memchr(const void *ptr, int ch, size_t count);
	int ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
	int ft_strlen(const char *str);
	size_t ft_strlcpy(char *dst, const char *src, size_t size);
	size_t ft_strlcat(char *dst, const char *src, size_t size);
	char *ft_strchr(const char *str, int c);
	char *ft_strrchr(const char *str, int c);
	char *ft_strnstr(const char *s1, const char *s2, size_t len);
	int ft_strncmp(const char *str1, const char *str2, size_t num);
	int ft_atoi(char *str);
	int ft_isalpha(int c);
	int ft_isdigit(int c);
	int ft_isalnum(int c);
	int ft_isascii(int c);
	int ft_isprint(int c);
	int ft_toupper(int c);
	int ft_tolower(int c);
	void *ft_calloc(size_t nmemb, size_t size);
	char *ft_strdup(const char *s);
	char *ft_substr(char const *s, unsigned int start, size_t len);
	char *ft_strjoin(char const *s1, char const *s2);
	char *ft_strtrim(char const *s1, char const *set);
	char **ft_split(char const *s, char c);
	char *ft_itoa(int n);
	char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
	void ft_putchar_fd(char c, int fd);
	void ft_putstr_fd(char *s, int fd);
	void ft_putendl_fd(char *s, int fd);
	void ft_putnbr_fd(int n, int fd);
	char *ft_itoagr(long long n, int gr);
	void ft_strlower(char *result);
	int ft_strcatchr(char *str, char c);
	char *ft_symclone(char sym, int num);
	int ft_strlens(const char *str);

#endif
