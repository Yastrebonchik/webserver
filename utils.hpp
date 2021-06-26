//
// Created by Karyn Cedra on 6/23/21.
//

#ifndef WEBSERVER_UTILS_HPP
#define WEBSERVER_UTILS_HPP

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string>
# define BUFFER_SIZE 32

char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
std::string	mimeDetect(std::string file);

#endif //WEBSERVER_UTILS_HPP
