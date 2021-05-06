# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/27 16:34:05 by kcedra            #+#    #+#              #
#    Updated: 2021/05/06 19:16:32 by kcedra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = libft.a

HEADER = libft.h

SOURCES = ft_memchr.cpp ft_strlcpy.cpp ft_memccpy.cpp ft_strlen.cpp ft_atoi.cpp ft_memcpy.cpp ft_strmapi.cpp ft_bzero.cpp ft_memset.cpp ft_strncmp.cpp\
ft_calloc.cpp ft_putchar_fd.cpp ft_strnstr.cpp ft_isalnum.cpp ft_putendl_fd.cpp ft_strrchr.cpp ft_isalpha.cpp ft_putnbr_fd.cpp ft_strtrim.cpp\
ft_isascii.cpp ft_putstr_fd.cpp ft_substr.cpp ft_isdigit.cpp ft_split.cpp ft_tolower.cpp ft_isprint.cpp ft_strchr.cpp ft_toupper.cpp ft_itoa.cpp\
ft_strdup.cpp ft_strjoin.cpp ft_strlcat.cpp ft_memcmp.cpp ft_memmove.cpp get_next_line.cpp get_next_line_utils.cpp ft_abs.cpp ft_min_of_2.cpp

O_FILES = $(SOURCES:.cpp=.o)

BONUS_SOURCES = ft_lstnew.cpp ft_lstadd_back.cpp ft_lstadd_front.cpp ft_lstclear.cpp ft_lstlast.cpp ft_lstsize.cpp ft_lstdelone.cpp ft_lstiter.cpp\
ft_lstmap.cpp

BONUS_O_FILES = $(BONUS_SOURCES:.cpp=.o)

FLAGS = -Wall -Wextra -Werror

.cpp.o:
	$(CC) $(FLAGS) -c $< -o ${<:.cpp=.o}

all: $(NAME)

$(NAME): $(O_FILES) $(HEADER)
	ar rcs $(NAME) $(O_FILES)

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

bonus: $(O_FILES) $(BONUS_O_FILES)
	ar rcs $(NAME) $(O_FILES) $(BONUS_O_FILES)

re:	fclean all
